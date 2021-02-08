/*****************************************************************
 * \file   FakeStack.h
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
 * This is an basic implementation of a Stack. It uses a List internaly to store the Stack elements.
 *
 */
template<typename T>
class FAKE_API FakeStack
	{
	private:
		FakeList<T> List;

	public:

		/**
		 *
		 * Empty constructor.
		 *
		 */
		FakeStack()
			{
			}

		/**
		 *
		 * Empty destructor.
		 *
		 */
		~FakeStack()
			{
			}

		/**
		 *
		 * Appends a new element to the stack.
		 *
		 * @param value The value which should be added to the stack.
		 */
		void Push(T value)
			{
			List.Append(value);
			}

		/**
		 *
		 * Removes the current element from the stack.
		 *
		 */
		void Pop()
			{
			List.RemoveLast();
			}

		/**
		 *
		 * Returns the current element from the stack.
		 *
		 * @return Returns the current element from the stack.
		 */
		T Top()
			{
			return List.GetLast();
			}

		/**
		 *
		 * Returns true if the stack is empty.
		 *
		 * @return Returns true if the stack is empty.
		 */
		bool IsEmpty()
			{
			return List.IsEmpty();
			}

		/**
		 *
		 * Returns the size of the current stack.
		 *
		 * @return Returns the size of the current stack.
		 */
		uint32 Size()
			{
			return List.Size();
			}

		/**
		 * 
		 * Clears the Stack.
		 * 
		 */
		void Clear()
			{
			List.Clear();
			}

		/**
		 *
		 * Prints the Stack to the console.
		 *
		 */
		void Print()
			{
			List.Print();
			}

		/**
		 *
		 * Writes the hole Stack into the output stream.
		 *
		 * @param stream The stream, which should be filled with the content of the Stack.
		 * @param stack The Stack, which should be written to the stream.
		 * @return Returns the stream, which was filled with the content of the Stack.
		 *
		 */
		friend std::ostream &operator<<(std::ostream &stream, FakeStack<T> &stack)
			{
			while (!stack.IsEmpty())
				{
				T content = stack.Top();
				stack.Pop();
				stream << content << ", ";
				}

			return stream << "\n";
			}
	};

typedef FakeStack<int> FakeStackInt;
typedef FakeStack<float> FakeStackFloat;
typedef FakeStack<double> FakeStackDouble;
typedef FakeStack<const char*> FakeStackString;
typedef FakeStack<short> FakeStackShort;
typedef FakeStack<long> FakeStackLong;
typedef FakeStack<bool> FakeStackBool;

