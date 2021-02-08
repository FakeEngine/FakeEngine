/*****************************************************************
 * \file   FakeQueue.h
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

#include "FakeList.h"

/**
 *
 * This is an basic implementation of a Queue. It uses a List internaly to store the Queue elements.
 *
 */
template<typename T>
class FAKE_API FakeQueue
	{
	private:
		FakeList<T> List;

	public:

		/**
		 *
		 * Empty constructor.
		 *
		 */
		FakeQueue()
			{
			}

		/**
		 *
		 * Empty destructor.
		 *
		 */
		~FakeQueue()
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
			List.Append(value);
			}

		/**
		 *
		 * Removes the last element from the Queue.
		 *
		 */
		void Dequeue()
			{
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
			return List.Size();
			}

		/**
		 * 
		 * Clears the Queue.
		 * 
		 */
		void Clear()
			{
			List.Clear();
			}

		/**
		 *
		 * Prints the Queue to the console.
		 *
		 */
		void Print()
			{
			List.Print();
			}

		/**
		 *
		 * Writes the hole Queue into the output stream.
		 *
		 * @param stream The stream, which should be filled with the content of the Queue.
		 * @param queue The Queue, which should be written to the stream.
		 * @return Returns the stream, which was filled with the content of the Queue.
		 */
		friend std::ostream &operator<<(std::ostream &stream, FakeQueue<T> &queue)
			{
			while (!queue.IsEmpty())
				{
				T content = queue.Front();
				queue.Dequeue();
				stream << content << ", ";
				}

			return stream << "\n";
			}
	};

typedef FakeQueue<int> FakeQueueInt;
typedef FakeQueue<float> FakeQueueFloat;
typedef FakeQueue<double> FakeQueueDouble;
typedef FakeQueue<const char *> FakeQueueString;
typedef FakeQueue<short> FakeQueueShort;
typedef FakeQueue<long> FakeQueueLong;
typedef FakeQueue<bool> FakeQueueBool;

