/*****************************************************************
 * \file   FakeList.h
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

/**
 *
 * This is a basic implementation of a linked list.
 *
 */
template<typename T>
class FAKE_API FakeList
	{
	private:

		struct Node
			{
			T Value;
			Node *Next;
			Node(T value) : Value(value), Next(nullptr) {}
			};

		Node *Root;
		uint32 Length;

		void Append(Node *parent, T value)
			{
			if (parent->Next == nullptr)
				{
				parent->Next = new Node(value);
				++Length;
				}
			else
				{
				Append(parent->Next, value);
				}
			}

	public:

		/**
		 *
		 * Basic constructor that initializes the Root node with nullptr and the Size with 0.
		 *
		 */
		FakeList()
			{
			Root = nullptr;
			Length = 0;
			}

		/**
		 *
		 * Removes every list element and the root node.
		 *
		 */
		~FakeList()
			{

			}

		/**
		 *
		 * Appends the value at the end of the List.
		 *
		 * @param value The value that should be added to the list.
		 */
		void Append(T value)
			{
			if (Root == nullptr)
				{
				Root = new Node(value);
				++Length;
				}
			else
				{
				Append(Root, value);
				}
			}

		/**
		 *
		 * Inserts the value to the begin of the List.
		 *
		 * @param value The value that should be added to the list.
		 */
		void Insert(T value)
			{
			Node *node = new Node(value);
			++Length;

			node->Next = Root;
			Root = node;
			}

		/**
		 *
		 * Returns the first element of the list.
		 *
		 * @return Returns the first element of the list.
		 */
		T GetFirst()
			{
			return Root->Value;
			}

		/**
		 *
		 * Returns the last element of the list.
		 *
		 * @return Returns the last element of the list.
		 */
		T GetLast()
			{
			Node *current = Root;
			FAKE_ASSERT(current, "Root was nullptr!");

			while (current->Next != nullptr)
				{
				current = current->Next;
				}

			return current->Value;
			}

		/**
		 *
		 * Gets a element at the specified index.
		 *
		 * @param index The index at which the element should be returned.
		 * @return Returns a element at the specified index.
		 */
		T Get(uint32 index)
			{
			if (index <= 0)
				return GetFirst();

			if (index >= Length)
				return GetLast();

			Node *current = Root;
			FAKE_ASSERT(current, "Root was nullptr!");
			T ret = NULL;
			uint32 i = 0;

			while (current != nullptr)
				{
				if (i == index)
					{
					ret = current->Value;
					break;
					}

				current = current->Next;
				i++;
				}

			return ret;
			}

		/**
		 *
		 * Removes the first element in the List.
		 *
		 */
		void RemoveFirst()
			{
			Node *tmp = Root;
			FAKE_ASSERT(tmp, "Root was nullptr!");
			Root = Root->Next;

			delete tmp;
			tmp = nullptr;
			--Length;
			}

		/**
		 *
		 * Removes the last element in the List.
		 *
		 */
		void RemoveLast()
			{
			if (Length == 1)
				{
				delete Root;
				Root = nullptr;
				Length = 0;
				return;
				}

			--Length;
			Node *current = Root;
			FAKE_ASSERT(current, "Root was nullptr!");

			while (current != nullptr)
				{
				if (current->Next->Next == nullptr)
					{
					delete current->Next;
					current->Next = nullptr;
					break;
					}

				current = current->Next;
				}
			}

		/**
		 *
		 * Removes the element at the specified index.
		 *
		 * @param index The index at which the element should be returned.
		 */
		void Remove(uint32 index)
			{
			if (index == 0)
				{
				RemoveFirst();
				return;
				}

			if (Length == index)
				{
				RemoveLast();
				return;
				}

			Node *current = Root;
			FAKE_ASSERT(current, "Root was nullptr!");
			uint32 i = 0;
			--Length;

			while (current != nullptr)
				{
				if ((i + 1) == index)
					{
					Node *tmp = current->Next;
					current->Next = current->Next->Next;

					delete tmp;
					tmp = nullptr;

					break;
					}
				current = current->Next;
				}
			}

		/**
		 *
		 * Removes all elements of the List and deletes the Root node.
		 *
		 */
		void RemoveAll()
			{
			Clear();
			delete Root;
			}

		/**
		 *
		 * Returns true if the List is empty.
		 *
		 * @return Returns true if the List is empty.
		 */
		bool IsEmpty()
			{
			return Length == 0;
			}

		/**
		 *
		 * Returns the size of the List.
		 *
		 * @return Returns the size of the List.
		 */
		uint32 Size()
			{
			return Length;
			}

		/**
		 *
		 * Removes all elements of the List.
		 *
		 */
		void Clear()
			{
			if (Length > 0)
				{
				Node *current = Root;
				FAKE_ASSERT(current != nullptr, "Root was nullptr!");

				while (current != nullptr)
					{
					Node *tmp = current->Next;
					delete current;
					current = tmp;
					}

				Root = nullptr;
				Length = 0;
				}
			}

		/**
		 *
		 * Converts the List to an array.
		 *
		 * @return Returns a List filled with the data.
		 */
		T *ToArray()
			{
			T *arr = new T[Length];
			Node *current = Root;
			FAKE_ASSERT(current, "Root was nullptr!");
			uint32 i = 0;

			while (current != nullptr)
				{
				arr[i] = current->Value;
				++i;
				current = current->Next;
				}

			return arr;
			}

		/**
		 *
		 * Prints the List to the console.
		 *
		 */
		void Print()
			{
			if (Length == 0)
				{
				FAKE_LOG_WARN("List was empty!");
				return;
				}

			Node *current = Root;
			FAKE_ASSERT(current, "Root was nullptr!");

			while (current != nullptr)
				{
				std::cout << current->Value << std::endl;
				current = current->Next;
				}
			}

		/**
		 *
		 * Writes the hole List into the output stream.
		 *
		 * @param stream The stream, which should be filled with the content of the List.
		 * @param list The List, which should be written to the stream.
		 * @return Returns the stream, which was filled with the content of the List.
		 */
		friend std::ostream &operator<<(std::ostream &stream, FakeList<T> &list)
			{
			Node *current = list.Root;
			FAKE_ASSERT(current, "Root was nullptr!");
			uint32 i = 0;

			stream << "[";
			while (current != nullptr)
				{
				if ((i + 1) == list.Size())
					{
					stream << current->Value;
					}
				else
					{
					stream << current->Value << ",";
					}

				++i;
				current = current->Next;
				}
			stream << "]";

			return stream;
			}
	};

typedef FakeList<int> FakeListInt;
typedef FakeList<float> FakeListFloat;
typedef FakeList<double> FakeListDouble;
typedef FakeList<const char*> FakeListString;
typedef FakeList<short> FakeListShort;
typedef FakeList<long> FakeListLong;
typedef FakeList<bool> FakeListBool;

