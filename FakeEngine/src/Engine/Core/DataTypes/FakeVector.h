/*****************************************************************
 * \file   FakeVector.h
 * \brief  
 * 
 * \author Can Karka
 * \date   January 2021
 * 
 * Copyright (C) 2021 Can Karka
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *********************************************************************/

#pragma once

#include "Engine/Core/FakeCore.h"

 /**
  *
  * This class is used as an iterator over the FakeVector.
  * It provides range based for loops for the FakeVector and much more.
  *
  */
template<typename Vector>
class FAKE_API FakeVectorIterator
	{
	public:
		using ValueType = typename Vector::ValueType;

	private:
		ValueType *Ptr;

	public:

		/**
		 *
		 * constructor that initializes the Vector instance.
		 *
		 * @param ptr The pointer type of an element of the Vector.
		 */
		FakeVectorIterator(ValueType *ptr)
			: Ptr(ptr)
			{
			}

		/**
		 *
		 * Returns a iterator pointing to the next element of the FakeVector.
		 *
		 * @return Returns a iterator pointing to the next element of the FakeVector.
		 */
		FakeVectorIterator &operator++()
			{
			Ptr++;
			return *this;
			}

		/**
		 *
		 * Returns a iterator pointing to the next element of the FakeVector.
		 *
		 * @return Returns a iterator pointing to the next element of the FakeVector.
		 */
		FakeVectorIterator &operator++(int)
			{
			FakeVectorIterator it = *this;
			++(*this);
			return it;
			}

		/**
		 *
		 * Returns a iterator pointing to the previous element of the FakeVector.
		 *
		 * @return Returns a iterator pointing to the previous element of the FakeVector.
		 */
		FakeVectorIterator &operator--()
			{
			Ptr--;
			return *this;
			}

		/**
		 *
		 * Returns a iterator pointing to the previous element of the FakeVector.
		 *
		 * @return Returns a iterator pointing to the previous element of the FakeVector.
		 */
		FakeVectorIterator &operator--(int)
			{
			FakeVectorIterator it = *this;
			--(*this);
			return it;
			}

		/**
		 *
		 * Returns the FakeVector element at the specified index.
		 *
		 * @param index The index specifying which ValueType should be returned.
		 * @return Returns Returns the FakeVector element at the specified index.
		 */
		ValueType &operator[](int index)
			{
			return *(Ptr + index);
			}

		/**
		 *
		 * Returns the FakeVector element at the specified index.
		 *
		 * @param index The index specifying which ValueType should be returned.
		 * @return Returns Returns the FakeVector element at the specified index.
		 */
		const ValueType &operator[](int index) const
			{
			return *(Ptr + index);
			}

		/**
		 *
		 * The overloaded -> operator.
		 *
		 * @return Returns the value type of the Iterator.
		 */
		ValueType *operator->()
			{
			return Ptr;
			}

		/**
		 *
		 * The overloaded -> operator.
		 *
		 * @return Returns the value type of the Iterator.
		 */
		ValueType *operator->() const
			{
			return Ptr;
			}

		/**
		 *
		 * The overloaded dereferencing operator.
		 *
		 * @return Returns the dereferenced value of the Iterator.
		 */
		ValueType &operator*()
			{
			return *Ptr;
			}

		/**
		 *
		 * Overloaded == operator.
		 *
		 * @param other The value which should be compared with.
		 * @return Returns true if the iterators are equal.
		 */
		bool operator==(const FakeVectorIterator &other)
			{
			return Ptr == other.Ptr;
			}

		/**
		 *
		 * Overloaded == operator.
		 *
		 * @param other The value which should be compared with.
		 * @return Returns true if the iterators are equal.
		 */
		bool operator==(const FakeVectorIterator &other) const
			{
			return Ptr == other.Ptr;
			}

		/**
		 *
		 * Overloaded != operator.
		 *
		 * @param other The value which should be compared with.
		 * @return Returns true if the iterators are not equal.
		 */
		bool operator!=(const FakeVectorIterator &other)
			{
			return !(*this == other);
			}

		/**
		 *
		 * Overloaded != operator.
		 *
		 * @param other The value which should be compared with.
		 * @return Returns true if the iterators are not equal.
		 */
		bool operator!=(const FakeVectorIterator &other) const
			{
			return !(*this == other);
			}
	};

/**
 *
 * This is an implementation of a heap based Array.
 *
 * @attention This class is not finished yet.
 *
 */
template<typename T>
class FAKE_API FakeVector
	{
	private:
		T *Data = nullptr;
		uint32 _Size = 0;
		uint32 _Capacity = 0;

		/**
		 *
		 * Reallocates space to store the data into the array.
		 *
		 * @param newCapacity The new size that should the array have allocated.
		 */
		void ReAllocate(uint32 newCapacity)
			{
			// Allocate new block of memory
			T *newBlock = (T *)::operator new(newCapacity * sizeof(T));

			// move from old block to new block

			// For downsizing the memory
			if (newCapacity < _Size)
				_Size = newCapacity;

			for (uint32 i = 0; i < _Size; ++i)
				new (&newBlock[i]) T(std::move(Data[i]));

			// Delete old block
			for (uint32 i = 0; i < _Size; ++i)
				Data[i].~T();

			::operator delete(Data, _Capacity * sizeof(T));

			Data = newBlock;
			_Capacity = newCapacity;
			}

	public:

		using ValueType = T;
		using Iterator = FakeVectorIterator<FakeVector<T>>;

		/**
		 *
		 * Basic constructor that allocates enough space for 2 elements.
		 *
		 */
		FakeVector()
			{
			ReAllocate(2);
			}

		/**
		 *
		 * destructor that removes all elements from the disk and frees the memory.
		 *
		 */
		~FakeVector()
			{
			Clear();
			::operator delete(Data, _Capacity * sizeof(T));
			}

		/**
		 *
		 * pushes a new Element at the end of the array and reAllocates more memory, if the array is too small.
		 *
		 * @param value The new value that should get appended to the array.
		 */
		void PushBack(const T &value)
			{
			if (_Size >= _Capacity)
				{
				ReAllocate(_Capacity + _Capacity / 2);
				}

			Data[_Size] = value;
			++_Size;
			}

		/**
		 *
		 * pushes a new Element at the end of the array and reAllocates more memory, if the array is too small.
		 *
		 * @param value The new value that should get appended to the array.
		 */
		void PushBack(T &&value) noexcept
			{
			if (_Size >= _Capacity)
				{
				ReAllocate(_Capacity + _Capacity / 2);
				}

			Data[_Size] = std::move(value);
			++_Size;
			}

		/**
		 *
		 * Constructs a new element of type T and stores it into the end of the array.
		 *
		 * @param args The data, that the constructor of the type T needs.
		 * @return Returns the new instance that was created and stored into the end of the array.
		 */
		template<typename... Args>
		T &EmplaceBack(Args&&... args)
			{
			if (_Size >= _Capacity)
				{
				ReAllocate(_Capacity + _Capacity / 2);
				}

			new(&Data[_Size]) T(std::forward<Args>(args)...);
			++_Size;
			return Data[_Size];
			}

		/**
		 *
		 * Destructs the last element of the Array and removes it from the array.
		 *
		 */
		void PopBack()
			{
			if (_Size > 0)
				{
				--_Size;
				Data[_Size].~T();
				}
			}

		/**
		 *
		 * Destructs and removes all elements from the array.
		 *
		 */
		void Clear()
			{
			for (uint32 i = 0; i < _Size; ++i)
				Data[i].~T();

			_Size = 0;
			}

		/**
		 *
		 * Prints the array to the console.
		 *
		 */
		void Print()
			{
			for (uint32 i = 0; i < _Size; ++i)
				std::cout << Data[i] << std::endl;
			}

		/**
		 *
		 * Returns the current amount of elements that the array has.
		 *
		 * @return Returns the current amount of elements that the array has.
		 */
		uint32 Size() const { return _Size; }

		/**
		 *
		 * Returns the current size on the heap that the array has allocated.
		 *
		 * @return Returns the current size on the heap that the array has allocated.
		 */
		uint32 Capacity() const { return _Capacity; }

		/**
		 *
		 * Returns the iterator pointing to the first element of the Vector.
		 *
		 * @return Returns the iterator pointing to the first element of the Vector.
		 */
		Iterator begin()
			{
			return Iterator(Data);
			}

		/**
		 *
		 * Returns the iterator pointing outside of the Vector.
		 *
		 * @return Returns the iterator pointing outside of the Vector.
		 */
		Iterator end()
			{
			return Iterator(Data + _Size);
			}

		/**
		 *
		 * Returns the element of the array at the specified index.
		 *
		 * @param i The specified index at which the element should be returned.
		 * @return Returns the element at index i.
		 */
		T &operator[](uint32 i) { return Data[i]; }

		/**
		 *
		 * Returns the element of the array at the specified index.
		 *
		 * @param i The specified index at which the element should be returned.
		 * @return Returns the element at index i.
		 */
		const T &operator[](uint32 i) const { return Data[i]; }

		/**
		 *
		 * Writes the hole array into the output stream.
		 *
		 * @param stream The stream, which should be filled with the content of the array.
		 * @param vector The array, which should be written to the stream.
		 * @return Returns the stream, which was filled with the content of the array.
		 */
		friend std::ostream &operator<<(std::ostream &stream, const FakeVector<T> vector)
			{
			for (uint32 i = 0; i < vector.Size(); ++i)
				stream << vector[i] << std::endl;

			return stream;
			}
	};
