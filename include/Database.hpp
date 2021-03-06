/*
    BSD 3-Clause License
    
    Copyright (c) 2021, SudoCpp
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef SIMPLEX_DATABASE_HPP
#define SIMPLEX_DATABASE_HPP

#include "string.hpp"
#include "DataTable.hpp"
#include "object.hpp"
#include "Exception.hpp"
#include "Array.hpp"

namespace simplex
{
    class DatabaseException : public Exception
	{
		public:
            DatabaseException(const string text, const char* fileName, const int lineNumber, const char* className, const char* methodName)
            : Exception{text, fileName, lineNumber, className, methodName}
            { 
                exceptionType = "DatabaseException";
            }
	};

    class DatabaseStatement : public object
    {
        public:
        const string statementQuery;
        DatabaseStatement(const string& statementQuery) 
        : statementQuery{statementQuery}
        {}
        virtual ~DatabaseStatement() = default;
        virtual DatabaseStatement& bind(const string& text) = 0;
        virtual DatabaseStatement& bind(int number) = 0;
        virtual DatabaseStatement& bind(double number) = 0;
        virtual DatabaseStatement& bind(const char* blob, int blobSize) = 0;
        //Relying on RVO 
        virtual DataTable execute() = 0;
    };

    class DatabaseCredentials : public object
    {
        public:
        string username;
        string password;
        string databaseAddress;
        string databaseName;
        DatabaseCredentials(string username, string password, string databaseAddress, string databaseName) 
        : username{username}, password{password}, databaseAddress{databaseAddress}, databaseName{databaseName} 
        {}
    };

    class Database : public object
    {
        DatabaseCredentials credentials;
        public:
        Database(const DatabaseCredentials& connectionSettings) 
        : credentials{connectionSettings} 
        {}
        virtual ~Database()
        {
            for(DatabaseStatement* statement : statements)
                delete statement;
        }
        
        virtual DataTable query(const string& sqlQuery) = 0;
        virtual DatabaseStatement& prepare(const string& sqlQuery) = 0;
        virtual Array<string> getTableNames() = 0;
        virtual Array<string> getColumnNames(const string& tableName) = 0;
        virtual string getColumnType(const string& tableName, const string& columnName) = 0;

        protected:
        Array<DatabaseStatement*> statements;
    };
}

#endif //SIMPLEX_DATABASE_HPP