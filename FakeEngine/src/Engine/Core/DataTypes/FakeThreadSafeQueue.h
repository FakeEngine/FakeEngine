/*****************************************************************
 * \file   FakeThreadSafeQueue.h
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
class FakeThreadSafeQueue
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
		FakeThreadSafeQueue()
			{
			}

		/**
		 *
		 * Empty destructor.
		 *
		 */
		~FakeThreadSafeQueue()
			{
			}

		/**
		 *
		 * Appends a new item to the Queue.
		 *
		 * @param value The Value which should be added to the Queue.
		 */
		void Enqueue(const T &value)
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
		void Dequeue()
			{
			std::scoped_lock lock(Mutex);
			List.RemoveFirst();
			}

		/**
		 *
		 * Returns the current element from the Queue.
		 *
		 * @return Returns the current element from the Queue.
		 */
		T Front()
			{
			std::scoped_lock lock(Mutex);
			return List.GetFirst();
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
		friend std::ostream &operator<<(std::ostream &stream, FakeThreadSafeQueue<T> &queue)
			{
			std::scoped_lock lock(queue.Mutex);

			while (!queue.IsEmpty())
				{
				T content = queue.Front();
				queue.Dequeue();
				stream << content << ", ";
				}

			return stream << "\n";
			}
	};

typedef FakeThreadSafeQueue<int> FakeTSQueueInt;
typedef FakeThreadSafeQueue<float> FakeTSQueueFloat;
typedef FakeThreadSafeQueue<double> FakeTSQueueDouble;
typedef FakeThreadSafeQueue<const char*> FakeTSQueueString;
typedef FakeThreadSafeQueue<short> FakeTSQueueShort;
typedef FakeThreadSafeQueue<long> FakeTSQueueLong;
typedef FakeThreadSafeQueue<bool> FakeTSQueueBool;

