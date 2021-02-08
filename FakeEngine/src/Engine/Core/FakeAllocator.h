/*****************************************************************
 * \file   FakeAllocator.h
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
 * This class is an implementation of a custom Allocator to store any data on the heap.
 *
 * You can use this class to store texture pixel data or buffer data
 *
 * ### Usage
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
 * FakeAllocator allocator;
 * allocator.Allocate(42);
 * allocator.Write(<MyData as void*>, <MySize as unsigned int>, <My Offset as unsigned int (defaulted to 0)>);
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
struct FAKE_API FakeAllocator
	{
	Byte *Data;		/**< Storage to store the allocated Data in */
	uint32 Size;	/**< Size of the allocated Data */

	/**
	 *
	 * Constructor which initializes the Data and Size with nullptr and 0.
	 *
	 */
	FakeAllocator()
		: Data(nullptr), Size(0)
		{
		}

	/**
	 *
	 * Constructor which sets the Data provided in arguments.
	 *
	 * @param data The data which should be allocated
	 * @param size The Size of the data which should be stored
	 */
	FakeAllocator(Byte *data, uint32 size)
		: Data(data), Size(size)
		{
		}

	/**
	 *
	 * Copies the data provided in the arguments to a new Allocator Instance.
	 *
	 * @param data The Data, which should be copied
	 * @param size The Size of the Data, which shoule be copied
	 * @return A new Instance of The Allocator class with the given arguments already allocated on the heap
	 */
	static FakeAllocator Copy(void *data, uint32 size)
		{
		FakeAllocator buffer;
		buffer.Allocate(size);
		memcpy(buffer.Data, data, size);
		return buffer;
		}

	/**
	 *
	 * Allocates dynamically storage to store Data in the Allocator.
	 *
	 * @param size The size to allocate that amount on the heap
	 */
	void Allocate(uint32 size)
		{
		delete[] Data;
		Data = nullptr;

		if (size == 0)
			return;

		Data = new Byte[size];
		Size = size;
		}

	/**
	 *
	 * Allocates memory with a specified alignment.
	 *
	 * @param size The size of the allocation in bytes.
	 * @param alignment The memory alignment in bytes (must be a power of 2).
	 * @return A pointer to the allocated block of memory. The pointer is a multiple of alignment.
	 */
	static void *Allocate(uint64 size, uint64 alignment = 16)
		{
		return _aligned_malloc((size_t)size, (size_t)alignment);
		}

	/**
	 *
	 * Frees a block of allocated memory.
	 *
	 * @param memory A pointer to the memory block which should be deallocated.
	 */
	static void Free(void *memory)
		{
		_aligned_free(memory);
		}

	/**
	 *
	 * Initializes the Allocator with 0.
	 *
	 */
	void ZeroInitialize()
		{
		if (Data)
			memset(Data, 0, Size);
		}

	/**
	 *
	 * Writes the provided data into the Allocator Instance.
	 *
	 * @param data The Data, which should be written
	 * @param size The Size of the Data, which should be written
	 * @param offset The Offset, to be able to store the Data at any point in the Allocator
	 */
	void Write(void *data, uint32 size, uint32 offset = 0)
		{
		FAKE_ASSERT(offset + size <= Size, "Buffer Overflow!");
		memcpy(Data + offset, data, size);
		}

	/**
	 *
	 * Reads all bytes beginning from the offset of the current allocated data.
	 *
	 * @param offset The amount of bytes to skip before starting the reading process.
	 * @return Returns the data read from the allocated storage.
	 */
	template<typename T>
	T &Read(uint32 offset = 0)
		{
		return *(T*)(Data + offset);
		}

	/**
	 *
	 * Overloaded bool operator to be able to check, if the Data is set or is nullptr.
	 *
	 * @return Returns true, if the Data is not nullptr
	 */
	operator bool() const
		{
		return Data;
		}

	/**
	 *
	 * Overloaded Subscripting Operator to be able to access the Data in a Array-Style.
	 *
	 * @param i The index which should be accessed.
	 * @return The Data at index i
	 */
	Byte &operator[](uint32 i)
		{
		return Data[i];
		}

	/**
	 *
	 * Overloaded Subscripting Operator to be able to access the Data in a Array-Style.
	 *
	 * @param i The index which should be accessed.
	 * @return The Data at index i
	 */
	Byte &operator[](uint32 i) const
		{
		return Data[i];
		}

	/**
	 *
	 * Casts the Data into the desired type.
	 *
	 * @return The Data converted to the desired Type
	 */
	template<typename T>
	T *As()
		{
		return (T*) Data;
		}

	/**
	 *
	 * Returns the Size of the allocated Data.
	 *
	 * @return The Size of the allocated Data
	 */
	uint32 GetSize() const
		{
		return Size;
		}
	};
