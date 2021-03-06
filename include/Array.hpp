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

#ifndef SIMPLEX_ARRAY_HPP
#define SIMPLEX_ARRAY_HPP

#include <algorithm>
#include "Exception.hpp"
#include <vector>
#include <string>

namespace simplex
{
	template <typename ArrayMemberType> class Array
	{
		public:
			Array();
			Array(::std::initializer_list<ArrayMemberType> iList);
			Array(int arraySize, char* characterArray[]);
			Array(int arraySize, ArrayMemberType nativeArray[]);
			Array(::std::vector<ArrayMemberType> vectorObject);

			//Operators
            ArrayMemberType operator[](int index) const;
            ArrayMemberType& operator[](int index);

			//Methods
			Array<ArrayMemberType>& add(ArrayMemberType value);
			Array<ArrayMemberType>& add(ArrayMemberType value, int index);
			Array<ArrayMemberType>& add(::std::initializer_list<ArrayMemberType> iList);
			Array<ArrayMemberType>& add(Array<ArrayMemberType> arrayValues);
			Array<ArrayMemberType>& add(::std::vector<ArrayMemberType> arrayValues);
			
			static Array<ArrayMemberType> FromVector(::std::vector<ArrayMemberType> vectorObject);
			std::vector<ArrayMemberType> toVector() const;
			
			ArrayMemberType& at(int index);
            ArrayMemberType at(int index) const;

			Array<ArrayMemberType>& clear();
			
			Array<ArrayMemberType> getPartialArray(int start);
			Array<ArrayMemberType> getPartialArray(int start, int count);
			
			bool contains(ArrayMemberType value) const;
			int containsCount(ArrayMemberType value) const;
			int indexOf(ArrayMemberType value) const;
			int lastIndexOf(ArrayMemberType value) const;
			ArrayMemberType pop(bool returnValue = false);
			Array<ArrayMemberType>& push(ArrayMemberType value);
			
			Array<ArrayMemberType>& remove(ArrayMemberType value);
			Array<ArrayMemberType>& removeAll(ArrayMemberType value);
			Array<ArrayMemberType>& removeAt(int index);
			
			Array<ArrayMemberType>& reserveSpace(size_t spaceToReserve);
			
			Array<ArrayMemberType>& reverse();
			Array<ArrayMemberType>& reverseSort();
			struct sorter
			{
				inline bool operator() (ArrayMemberType type1, ArrayMemberType type2)
				{
					return ((::std::string)type1 < (::std::string)type2);
				}
			};
			Array<ArrayMemberType>& sort();
			
            auto begin()
			{
				return array_.begin();
			}
            auto end()
			{
				return array_.end();
			}
			
			size_t size() const;

		protected:
			::std::vector<ArrayMemberType> array_;
	};
}

#define __class__ "simplex::Array"

namespace simplex
{
    template <typename ArrayMemberType>
    Array<ArrayMemberType>::Array() {}

    template <typename ArrayMemberType>
    Array<ArrayMemberType>::Array(::std::initializer_list<ArrayMemberType> iList)
    {
        for (ArrayMemberType item : iList)
            add(item);
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>::Array(int arraySize, char* characterArray[])
    {
        for (int i = 0; i < arraySize; i++)
            array_.emplace_back(::std::string(characterArray[i]));
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>::Array(::std::vector<ArrayMemberType> vectorObject) : array_{vectorObject}
    {}

    //Operators
    template <typename ArrayMemberType>
    ArrayMemberType Array<ArrayMemberType>::operator[](int index) const
    {
        return at(index);
    }
    template <typename ArrayMemberType>
    ArrayMemberType& Array<ArrayMemberType>::operator[](int index)
    {
        return at(index);
    }

    //Methods
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(ArrayMemberType value)
    {
        array_.emplace_back(value);
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(ArrayMemberType value, int index)
    {
        if (index < size() + 1)
        {
            array_.insert(array_.begin() + index, value);
        }
        else
            throw IndexOutOfBoundsException{"Index "+ string::FromNumber(index) +" does not exist.", __ExceptionParams__};

        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(::std::initializer_list<ArrayMemberType> iList)
    {
        for (ArrayMemberType item : iList)
            add(item);
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(Array<ArrayMemberType> arrayValues)
    {
        array_.insert(array_.end(), arrayValues.begin(), arrayValues.end());
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(::std::vector<ArrayMemberType> arrayValues)
    {
        array_.insert(array_.end(), arrayValues.begin(), arrayValues.end());
        return *this;
    }
    
    template <typename ArrayMemberType>
    Array<ArrayMemberType> Array<ArrayMemberType>::FromVector(::std::vector<ArrayMemberType> vectorObject)
    {
        Array<ArrayMemberType> array{vectorObject};
        return array;
    }
    template <typename ArrayMemberType>
    ::std::vector<ArrayMemberType> Array<ArrayMemberType>::toVector() const
    {
        return array_;
    }

    template <typename ArrayMemberType>
    ArrayMemberType& Array<ArrayMemberType>::at(int index)
    {
        try
        {
            return array_.at(index);
        }
        catch (...)
        {
            throw IndexOutOfBoundsException("Index "+ string::FromNumber(index) +" does not exist.", __ExceptionParams__);
        }
    }
    template <typename ArrayMemberType>
    ArrayMemberType Array<ArrayMemberType>::at(int index) const
    {
        try
        {
            const ArrayMemberType temp = array_.at(index);
            return temp;
        }
        catch (...)
        {
            throw IndexOutOfBoundsException("Index "+ string::FromNumber(index) +" does not exist.", __ExceptionParams__);
        }
    }

    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::clear()
    {
        array_.clear();
        return *this;
    }

    template <typename ArrayMemberType>
    Array<ArrayMemberType> Array<ArrayMemberType>::getPartialArray(int start)
    {
        int arraySize = array_.size();
        if (start < 0)
            start = arraySize + start;

        if (start > arraySize)
            throw IndexOutOfBoundsException("Starting beyond size of Array.", __ExceptionParams__);

        return Array<ArrayMemberType>(::std::vector<ArrayMemberType>(array_.begin() + start, array_.end()));
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType> Array<ArrayMemberType>::getPartialArray(int start, int count)
    {
        int arraySize = array_.size();
        if (start < 0)
            start = arraySize + start;
        if (count < 0)
            count = arraySize - start + count;

        if (start > arraySize)
            throw IndexOutOfBoundsException("Starting beyond size of Array.", __ExceptionParams__);
        else if (start + count > arraySize)
            throw IndexOutOfBoundsException("Starting beyond size of Array.", __ExceptionParams__);

        if (start + count == arraySize)
            return Array<ArrayMemberType>(::std::vector<ArrayMemberType>(array_.begin() + start, array_.end()));
        else
            return Array<ArrayMemberType>(::std::vector<ArrayMemberType>(array_.begin() + start, array_.begin() + start + count));
    }
    
    template <typename ArrayMemberType>
    bool Array<ArrayMemberType>::contains(ArrayMemberType value) const
    {
        return (::std::find(array_.begin(), array_.end(), value) != array_.end()) ? true : false;
    }
    template <typename ArrayMemberType>
    int Array<ArrayMemberType>::containsCount(ArrayMemberType value) const
    {
        return ::std::count(array_.begin(), array_.end(), value);
    }
    template <typename ArrayMemberType>
    int Array<ArrayMemberType>::indexOf(ArrayMemberType value) const
    {
        return ::std::distance(array_.begin(), ::std::find(array_.begin(), array_.end(), value));
    }
    template <typename ArrayMemberType>
    int Array<ArrayMemberType>::lastIndexOf(ArrayMemberType value) const
    {
        int indexFromEnd = std::distance(array_.rbegin(), ::std::find(array_.rbegin(), array_.rend(), value));
        return array_.size() - indexFromEnd - 1;
    }
    template <typename ArrayMemberType>
    ArrayMemberType Array<ArrayMemberType>::pop(bool returnValue)
    {
        if(returnValue)
        {
            ArrayMemberType temp = array_.at(array_.size() - 1);
            array_.pop_back();
            return temp;
        }
        else
            array_.pop_back();
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::push(ArrayMemberType value)
    {
        add(value);
        return *this;
    }
    
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::remove(ArrayMemberType value)
    {
        int arraySize = size();
        for (int loop = 0; loop < arraySize; loop++)
            if (array_[loop] == value)
            {
                removeAt(loop);
                break;
            }

        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::removeAll(ArrayMemberType value)
    {
        array_.clear();
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::removeAt(int index)
    {
        array_.erase(array_.begin() + index);
        return *this;
    }
    
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::reserveSpace(size_t spaceToReserve)
    {
        array_.reserve(spaceToReserve);
        return *this;
    }
    
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::reverse()
    {
        ::std::reverse(array_.begin(), array_.end());
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::reverseSort()
    {
        sort();
        reverse();
        return *this;
    }

    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::sort()
    {
        ::std::sort(array_.begin(), array_.end(), sorter());
        return *this;
    }
    
    template <typename ArrayMemberType>
    size_t Array<ArrayMemberType>::size() const
    {
        return array_.size();
    }
}

#undef __class__

#endif // SIMPLEX_ARRAY_HPP