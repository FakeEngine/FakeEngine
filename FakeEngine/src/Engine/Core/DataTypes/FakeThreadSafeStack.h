/*****************************************************************
 * \file   FakeThreadSafeStack.h
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

#include <mutex>

#include "FakeList.h"

/**
 * 
 * .
 * 
 */
template<typename T>
class FakeThreadSafeStack
	{
	private:
		FakeList<T> List;
		std::mutex Mutex;

		std::mutex MUXMutex;
		std::condition_variable CVBlocking;

	public:

		/**
		 *
		 * Empty constructor.
		 *
		 */
		FakeThreadSafeStack()
			{
			}

		/**
		 *
		 * Empty destructor.
		 *
		 */
		~FakeThreadSafeStack()
			{
			}

		/**
		 *
		 * Appends a new item to the Queue.
		 *
		 * @param value The Value which should be added to the Queue.
		 */
		void Push(const T &value)
			{
			std::scoped_lock lock(Mutex);
			List.Append(value);

			std::unique_lock<std::mutex> ul(MUXMutex);
			CVBlocking.notify_one();
			}

		/**
		 *
		 * Removes the last element from the Queue.
		 *
		 */
		void Pop()
			{
			std::scoped_lock lock(Mutex);
			List.RemoveLast();
			}

		/**
		 *
		 * Returns the current element from the Queue.
		 *
		 * @return Returns the current element from the Queue.
		 */
		T Top()
			{
			std::scoped_lock lock(Mutex);
			return List.GetLast();
			}

		/**
		 *
		 * Returns true if the Queue is empty.
		 *
		 * @return Returns true if the Queue is empty.
		 */
		bool IsEmpty()
			{
			std::scoped_lock lock(Mutex);
			return List.IsEmpty();
			}

		/**
		 *
		 * Returns the size of the current Queue.
		 *
		 * @return Returns the size of the current Queue.
		 */
		uint32 Size()
			{
			std::scoped_lock lock(Mutex);
			return List.Size();
			}

		/**
		 *
		 * Clears the Queue.
		 *
		 */
		void Clear()
			{
			std::scoped_lock lock(Mutex);
			List.Clear();
			}

		/**
		 *
		 * Prints the Queue to the console.
		 *
		 */
		void Print()
			{
			std::scoped_lock lock(Mutex);
			List.Print();
			}

		/**
		 * 
		 * .
		 * 
		 */
		void Wait()
			{
			while (IsEmpty())
				{
				std::unique_lock<std::mutex> ul(MUXMutex);
				CVBlocking.wait(ul);
				}
			}

		/**
		 *
		 * Writes the hole Queue into the output stream.
		 *
		 * @param stream The stream, which should be filled with the content of the Queue.
		 * @param queue The Queue, which should be written to the stream.
		 * @return Returns the stream, which was filled with the content of the Queue.
		 */
		friend std::ostream &operator<<(std::ostream &stream, FakeThreadSafeStack<T> &stack)
			{
			std::scoped_lock lock(stack.Mutex);

			while (!stack.IsEmpty())
				{
				T element = stack.Top();
				stack.Pop();
				stream << element << std::endl;
				}

			return stream;
			}
	};

typedef FakeThreadSafeStack<int> FakeTSStackInt;
typedef FakeThreadSafeStack<float> FakeTSStackFloat;
typedef FakeThreadSafeStack<double> FakeTSStackDouble;
typedef FakeThreadSafeStack<const char*> FakeTSStackString;
typedef FakeThreadSafeStack<short> FakeTSStackShort;
typedef FakeThreadSafeStack<long> FakeTSStackLong;
typedef FakeThreadSafeStack<bool> FakeTSStackBool;

