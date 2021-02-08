/*****************************************************************
 * \file   FakeArray.h
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

#include "FakePch.h"
// #include "Engine/Core/FakeAllocator.h"

/**
 *
 * This is an implementation of a stack based Array.
 *
 * @attention This class is not finished yet.
 *
 */
template<typename T>
class FAKE_API FakeArray
	{
	private:
		int32 Count;
		int32 Capacity;
	//	FakeAllocator Allocation;

	public:

		FakeArray()
			: Count(0), Capacity(0)
			{
			}

		FakeArray(int32 capacity)
			: Count(0), Capacity(capacity)
			{
			if (Capacity > 0)
				{
			//	Allocation.Allocate(Capacity);
				}
			}

		FakeArray(const T *data, int32 length)
			{
			FAKE_ASSERT(length >= 0, "");
			Count = Capacity = length;
			if (length > 0)
				{
				// Allocation.Allocate(length);
				// FakeMemory::ConstructItems(Get(), data, length);
				}
			}

		FakeArray(const FakeArray &other)
			{
			Count = Capacity = other.Count;
			if (Capacity > 0)
				{
				// Allocation.Allocate(Capacity);
				// FakeMemory::ConstructItems(Get(), other.Get(), other.Count);
				}
			}

		FakeArray(const FakeArray &other, int32 extraSize)
			{
			FAKE_ASSERT(extraSize >= 0);
			Count = Capacity = other.Count + extraSize;
			if (Capacity > 0)
				{
				// Allocation.Allocate(Capacity);
				// FakeMemory::ConstructItems(Get(), other.Get(), other.Count);
				// FakeMemory::ConstructItems(Get() + other.Count, extraSize);
				}
			}

		template<typename F>
		explicit FakeArray(const FakeArray<F> &other) noexcept
			{
			Capacity = other.Capacity;
			Count = other.Count;
			if (Capacity > 0)
				{
				// Allocation.Allocate(Capacity);
				// FakeMemory::ConstructItems(Get(), other.Data, other.Count);
				}
			}

		FakeArray(FakeArray &&other) noexcept
			{
			Count = other.Count;
			Capacity = other.Capacity;
			other.Count = 0;
			other.Capacity = 0;
			//	Allocation.Swap(other.Allocation);
			}

		FakeArray &operator=(const FakeArray &other) noexcept
			{
			if (this != &other)
				{
				// FakeMemory::DestructItems(Get(), Count);
				if (Capacity < other.Count)
					{
					//Allocation.Free();
					Capacity = other.Count;
					Allocation.Allocate(Capacity);
					}

				Count = other.Count;
				// FakeMemory::ConstructItems(Get(), other.Get(), Count);
				}

			return *this;
			}

		FakeArray &operator=(FakeArray &&other) noexcept
			{
			if (this != &other)
				{
				// FakeMemory::DestructItems(Get(), Count);
				// Allocation.Free();
				Count = other.Count;
				Capacity = other.Capacity;
				other.Count = 0;
				other.Capacity = 0;
				// Allocation.Swap(other.Allocation);
				}

			return *this;
			}

		~FakeArray()
			{
			// FakeMemory::DestructItems(Get(), Count);
			}

		inline int32 GetCount() const
			{
			return Count;
			}

		inline int32 GetCapacity() const
			{
			return Capacity;
			}

		inline bool HasItems() const
			{
			return Count != 0;
			}

		inline bool IsEmpty() const
			{
			return Count == 0;
			}

		inline T *Get()
			{
			//	return Allocation.Get();
			return nullptr;
			}

		inline const T *Get() const
			{
			//	return Allocation.Get();
			return nullptr;
			}

		inline T &At(int32 index)
			{
			FAKE_ASSERT(index >= 0 && index < Count);
			return Get()[index];
			}

		inline const T &At(int32 index) const
			{
			FAKE_ASSERT(index >= 0 && index < Count);
			return Get()[index];
			}

		inline T &operator[](int32 index)
			{
			FAKE_ASSERT(index >= 0 && index < Count);
			return Get()[index];
			}

		inline const T &operator[](int32 index) const
			{
			FAKE_ASSERT(index >= 0 && index < Count);
			return Get()[index];
			}

		inline T &Last()
			{
			FAKE_ASSERT(Count > 0);
			return Get()[Count - 1];
			}

		inline const T &Last() const
			{
			FAKE_ASSERT(Count > 0);
			return Get()[Count - 1];
			}

		inline T &First()
			{
			FAKE_ASSERT(Count > 0);
			return Get()[0];
			}

		inline const T &First() const
			{
			FAKE_ASSERT(Count > 0);
			return Get()[0];
			}



		inline T *begin()
			{
			return &Get()[0];
			}

		inline const T *begin() const
			{
			return &Get()[0];
			}

		inline T *end()
			{
			return &Get()[Count];
			}

		inline const T *end() const
			{
			return &Get()[Count];
			}


		inline void Clear()
			{
			//	FakeMemory::DestructItems(Get(), Count);
			Count = 0;
			}

		void RemoveAll()
			{
			T *data = Get();
			for (int32 i = 0; i < Count; ++i)
				{
				if (data[i])
					{
					//	Delete(data[i]);
					}
				}
			Clear();
			}

		void SetCapacity(const int32 capacity, bool preserveContents = true)
			{
			if (capacity == Capacity)
				return;

			FAKE_ASSERT(capacity >= 0);
			const int32 count = preserveContents ? (Count < capacity ? Count : capacity) : 0;
			//	Allocation.Relocate(capacity, Count, count);
			Capacity = capacity;
			Count = count;
			}

		void Resize(int32 size, bool preserveContents = true)
			{
			if (Count > size)
				{
				//	FakeMemory::DestructItems(Get() + size, Count - size);
				}
			else
				{
				EnsureCapacity(size, preserveContents);
				//FakeMemory::ConstructItems(Get() + Count, size - Count);
				}

			Count = size;
			}

		void EnsureCapacity(int32 minCapacity, bool preserveContents = true)
			{
			if (Capacity < minCapacity)
				{
				const int32 capacity = Allocation.CalculateCapacityGrow(Capacity, minCapacity);
				SetCapacity(capacity, preserveContents);
				}
			}

		void SetAll(const T &value)
			{
			T *data = Get();
			for (int32 i = 0; i < Count; ++i)
				data[i] = value;
			}

		void Set(const T *data, int32 count)
			{
			EnsureCapacity(count, false);
			// FakeMemory::DestructItems(Get(), Count);
			Count = count;
			// FakeMemory::ConstructItems(Get(), data, Count);
			}

		void Add(const T &item)
			{
			EnsureCapacity(Count + 1);
			//	FakeMemory::ConstructItems(Get() + Count, &item, 1);
			++Count;
			}

		inline void Add(const FakeArray &other)
			{
			Add(other.Get(), other.GetCount());
			}

		template<typename F>
		inline void Add(const FakeArray<F> &other)
			{
			Add(other.Get(), other.Count());
			}

		inline void AddUnique(const T &item)
			{
			if (!Contains(item))
				Add(item);
			}

		inline void AddDefault(int32 count = 1)
			{
			EnsureCapacity(Count + count);
			//	FakeMemory::ConstructItems(Get() + count, count);
			Count += count;
			}

		inline void AddUninitialized(int32 count = 1)
			{

			}
	};
