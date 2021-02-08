/*****************************************************************
 * \file   FakeBinaryTree.h
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
#include "FakeQueue.h"

/**
 *
 * The BinaryTree implementation is meant for Clients. They can use this class to store data in a BinaryTree structure.
 *
 * <b>In computing, binary trees are used in two very different ways:</b>
 *
 * First, as a means of accessing nodes based on some value or label associated with each node. Binary trees labelled this way are used to implement binary search trees and binary heaps, and are used for efficient searching and sorting. The designation of non-root nodes as left or right child even when there is only one child present matters in some of these applications, in particular, it is significant in binary search trees. However, the arrangement of particular nodes into the tree is not part of the conceptual information. For example, in a normal binary search tree the placement of nodes depends almost entirely on the order in which they were added, and can be re-arranged (for example by balancing) without changing the meaning.
 *
 * Second, as a representation of data with a relevant bifurcating structure. In such cases, the particular arrangement of nodes under and/or to the left or right of other nodes is part of the information (that is, changing it would change the meaning). Common examples occur with Huffman coding and cladograms. The everyday division of documents into chapters, sections, paragraphs, and so on is an analogous example with n-ary rather than binary trees.
 *
 * @see https://en.wikipedia.org/wiki/Binary_tree
 *
 */
template<typename T>
class FAKE_API FakeBinaryTree
	{
	private:

		struct Node
			{
			T Value;
			Node *Left, *Right;
			Node(T value) : Value(value), Left(nullptr), Right(nullptr) {}

			/**
			 *
			 * Calculates the Height of the current BT. A height is determined by the amount of levels a BT has.
			 *
			 * @return Returns the height of the current BT instance.
			 */
			uint32 CalcHeight()
				{
				uint32 leftVal = 0, rightVal = 0;

				if (this->Left)
					leftVal = this->Left->CalcHeight();

				if (this->Right)
					rightVal = this->Right->CalcHeight();

				return 1 + MAX(leftVal, rightVal);
				}
			};

		Node *Root;
		uint32 Length;

		/**
		 *
		 * Traverses trough the tree until the deepest node, so the node with no children is found and removes it.
		 *
		 * @param node The node, from which the tree should be traversed.
		 * @param dNode The node, from which the deepest duplicate should be found and removed.
		 */
		void RemoveDeepestNode(Node *node, Node *dNode)
			{
			FakeQueue<Node*> q;
			q.Enqueue(node);

			Node *temp;
			while (!q.IsEmpty())
				{
				temp = q.Front();
				q.Dequeue();

				if (temp == dNode)
					{
					delete temp;
					temp = nullptr;
					--Length;
					return;
					}

				if (temp->Right)
					{
					if (temp->Right == dNode)
						{
						delete temp->Right;
						temp->Right = nullptr;
						--Length;
						return;
						}
					else
						{
						q.Enqueue(temp->Right);
						}
					}

				if (temp->Left)
					{
					if (temp->Left == dNode)
						{
						delete temp->Left;
						temp->Left = nullptr;
						--Length;
						return;
						}
					else
						{
						q.Enqueue(temp->Left);
						}
					}
			}
		}

		/**
		 *
		 * Swaps both childrent of a given node, the left node will become the right node and the right node will become the left node.
		 *
		 * @param node The node which children should be swapped.
		 *
		 */
		void Swap(Node *node)
			{
			Node *temp = node->Left;
			node->Left = node->Right;
			node->Right = temp;
			}

	public:

		/**
		 *
		 * Constructor to initialize the Root node with NULL and the Length with 0.
		 *
		 */
		FakeBinaryTree()
			{
			Root = nullptr;
			Length = 0;
			}

		/**
		 *
		 * Destructor removes all nodes from the bt to not leak any memory and resets the Length to 0.
		 *
		 */
		~FakeBinaryTree()
			{
			RemoveAll();
			Length = 0;
			}

		/**
		 *
		 * Helper function which should add a value to the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real Append(Node*, T) function with the Root node.
		 *
		 * @param value The value which should be added to the tree.
		 *
		 */
		void Append(T value) { Append(Root, value); }

		/**
		 *
		 * The real Append function, which should add a value to the tree.
		 *
		 * @param node The node, from which the algorithm should search for a empty spot to append the new value into.
		 * @param value The value which should be added to the tree.
		 */
		void Append(Node *node, T value)
			{
			if (Root == nullptr)
				{
				Root = new Node(value);
				++Length;
				return;
				}

			FakeQueue<Node*> q;
			q.Enqueue(node);

			while (!q.IsEmpty())
				{
				Node *temp = q.Front();
				q.Dequeue();

				if (!temp->Left)
					{
					temp->Left = new Node(value);
					++Length;
					break;
					}
				else
					{
					q.Enqueue(temp->Left);
					}

				if (!temp->Right)
					{
					temp->Right = new Node(value);
					++Length;
					break;
					}
				else
					{
					q.Enqueue(temp->Right);
					}
				}
			}

		/**
		 *
		 * Helper function which should remove all nodes from the Tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real RemoveAll(Node*) function with the Root node.
		 *
		 */
		void RemoveAll() { RemoveAll(Root); }

		/**
		 *
		 * The real RemoveAll function, this function removes all nodes from the tree.
		 *
		 * @param node The node, from which the tree should be freed.
		 *
		 */
		void RemoveAll(Node *node)
			{
			if (node == nullptr)
				return;

			RemoveAll(node->Left);
			RemoveAll(node->Right);

			delete node;
			node = nullptr;
			}

		/**
		 *
		 * Helper function which should remove a particular value and it's node from the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real Remove(Node*, T) function with the Root node.
		 *
		 * @param value The value which should be removed from the BST.
		 * @return Returns the Node with the value which was deleted from the tree.
		 *
		 */
		Node *Remove(T value) { Remove(Root, value); }

		/**
		 *
		 * The real Remove function, this function removes a particular value and it's node from the tree.
		 *
		 * @param node The node, from which the algorithm should search for the value to delete.
		 * @param value The value, which should be searched for, to delete it from the tree.
		 * @return Returns the Node with the value which was deleted from the tree.
		 *
		 */
		Node *Remove(Node *node, T value)
			{
			if (node == nullptr)
				return nullptr;

			if (node->Left == nullptr && node->Right == nullptr)
				{
				if (node->Value == value)
					{
					return nullptr;
					}
				else
					{
					return node;
					}
				}

			FakeQueue<Node*> q;
			q.Enqueue(node);

			Node *temp;
			Node *keyNode = nullptr;

			while (!q.IsEmpty())
				{
				temp = q.Front();
				q.Dequeue();

				if (temp->Value == value)
					keyNode = temp;

				if (temp->Left)
					q.Enqueue(temp->Left);

				if (temp->Right)
					q.Enqueue(temp->Right);
				}

			if (keyNode == nullptr)
				{
				T x = temp->Value;
				RemoveDeepestNode(node, temp);
				keyNode->Value = x;
				}

			return node;
			}

		/**
		 *
		 * Helper function which should return the node with a particular value.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real GetNode(Node*, T) function with the Root node.
		 *
		 * @param value The value which should be searched for in the tree.
		 * @return Returns the node with the value which was searched for in the tree.
		 */
		Node *GetNode(T value) { return GetNode(Root, value); }

		/**
		 *
		 * The real GetNode function which should return the node with a particular value.
		 *
		 * @param node The node, from which the algorithm should search for the value.
		 * @param value The value which should be searched for in the tree.
		 * @return Returns the node with the value which was searched for in the tree.
		 */
		Node *GetNode(Node *node, T value)
			{
			if (!node)
				return nullptr;

			FakeQueue<Node*> q;
			q.Enqueue(node);

			while (!q.IsEmpty())
				{
				Node *current = q.Front();
				q.Dequeue();

				if (current->Left)
					q.Enqueue(current->Left);

				if (current->Right)
					q.Enqueue(current->Right);

				if (current->Value == value)
					return current;
				}

			return nullptr;
			}

		/**
		 *
		 * Helper function which should invert the hole tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real Invert(Node*) function with the Root node.
		 *
		 */
		void Invert() { Invert(Root); }

		/**
		 *
		 * The real Invert function, this function inverts the hole tree.
		 *
		 * @param node The node, from which the tree should be inverted.
		 *
		 */
		void Invert(Node *node)
			{
			if (node == nullptr)
				return;

			Swap(node);
			Invert(node->Left);
			Invert(node->Right);
			}

		/**
		 *
		 * Helper function which should find the lowest value in the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real FindMin(Node*) function with the Root node.
		 *
		 * @return Returns the lowest value found in the tree.
		 *
		 */
		T FindMin() { return FindMin(Root); }

		/**
		 *
		 * The real FindMin function, this function finds the lowest value placed in the tree and returns it.
		 *
		 * @param node The node, from which the lowest value should be found.
		 * @return Returns the lowest value found in the tree.
		 *
		 */
		T FindMin(Node *node)
			{
			FakeQueue<Node*> q;
			q.Enqueue(node);

			T min = fake_max_value<T>();
			while (!q.IsEmpty())
				{
				Node *current = q.Front();
				q.Dequeue();

				if (current->Left)
					q.Enqueue(current->Left);

				if (current->Right)
					q.Enqueue(current->Right);

				if (current->Value < min)
					min = current->Value;
				}

			return min;
			}

		/**
		 *
		 * Helper function which should find the highest value in the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real FindMax(Node*) function with the Root node.
		 *
		 * @return Returns the highest value found in the tree.
		 *
		 */
		T FindMax() { return FindMax(Root); }

		/**
		 *
		 * The real FindMax function, this function finds the highest value placed in the tree and returns it.
		 *
		 * @param node The node, from which the highest value should be found.
		 * @return Returns the highest value found in the tree.
		 *
		 */
		T FindMax(Node *node)
			{
			FakeQueue<Node*> q;
			q.Enqueue(node);

			T max = fake_min_value<T>();
			while (!q.IsEmpty())
				{
				Node *current = q.Front();
				q.Dequeue();

				if (current->Left)
					q.Enqueue(current->Left);

				if (current->Right)
					q.Enqueue(current->Right);

				if (current->Value > max)
					max = current->Value;
				}

			return max;
			}

		/**
		 *
		 * Helper function which should find the node with the lowest value in the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real FindMinNode(Node*) function with the Root node.
		 *
		 * @return Returns the node with the lowest value.
		 *
		 */
		Node *FindMinNode() { return FindMinNode(Root); }

		/**
		 *
		 * The real FindMinNode function, this function finds the node with the lowest value placed in the tree and returns it.
		 *
		 * @param node The node, from which the node with the lowest value should be found.
		 * @return Returns the node with the lowest value.
		 *
		 */
		Node *FindMinNode(Node *node)
			{
			FakeQueue<Node*> q;
			q.Enqueue(node);

			T min = fake_max_value<T>();
			Node *ret = nullptr;
			while (!q.IsEmpty())
				{
				Node *current = q.Front();
				q.Dequeue();

				if (current->Left)
					q.Enqueue(current->Left);

				if (current->Right)
					q.Enqueue(current->Right);

				if (current->Value < min)
					{
					min = current->Value;
					ret = current;
					}
				}

			return ret;
			}

		/**
		 *
		 * Helper function which should find the node with the highest value in the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real FindMaxNode(Node*) function with the Root node.
		 *
		 * @return Returns the node with the highest value.
		 *
		 */
		Node *FindMaxNode() { return FindMaxNode(Root); }

		/**
		 *
		 * The real FindMaxNode function, this function finds the node with the highest value placed in the tree and returns it.
		 *
		 * @param node The node, from which the node with the highest value should be found.
		 * @return Returns the node with the highest value.
		 *
		 */
		Node *FindMaxNode(Node *node)
			{
			FakeQueue<Node*> q;
			q.Enqueue(node);

			T max = fake_min_value<T>();
			Node *ret = nullptr;
			while (!q.IsEmpty())
				{
				Node *current = q.Front();
				q.Dequeue();

				if (current->Left)
					q.Enqueue(current->Left);

				if (current->Right)
					q.Enqueue(current->Right);

				if (current->Value > max)
					{
					max = current->Value;
					ret = current;
					}
				}

			return ret;
			}

		/**
		 *
		 * Helper function which should check if a value exists in the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real ValueExists(Node*, T) function with the Root node.
		 *
		 * @param value The value, which should be searched for in the tree.
		 * @return Returns true if the value has been found in the tree.
		 *
		 */
		bool ValueExists(T value) { return ValueExists(Root, value); }

		/**
		 *
		 * The real ValueExists function, this function should search for a value and return true if the value has been found in the tree.
		 *
		 * @param node The node, from which the algorithm should search for the value.
		 * @param value The value, which should be searched for in the tree.
		 * @return Returns true if the value has been found in the tree.
		 *
		 */
		bool ValueExists(Node *node, T value)
			{
			if (!node)
				return false;

			FakeQueue<Node*> q;
			q.Enqueue(node);

			while (!q.IsEmpty())
				{
				Node *current = q.Front();
				q.Dequeue();

				if (current->Left)
					q.Enqueue(current->Left);

				if (current->Right)
					q.Enqueue(current->Right);

				if (current->Value == value)
					return true;
				}

			return false;
			}

		/**
		 *
		 * Checks, if the tree is empty or not.
		 *
		 * @return Returns true if the Tree does not have any node.
		 *
		 */
		bool IsEmpty()
			{
			return Length == 0;
			}

		/**
		 *
		 * The Size is going to be incremented by every Append(T) call and is going to be decremented by every Remove(T) call.
		 *
		 * @return Returns the number of nodes the tree has.
		 *
		 */
		uint32 Size()
			{
			return Length;
			}

		/**
		 *
		 * Helper function which should calculate the height of the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real GetHeight(Node*) function with the Root node.
		 *
		 * @return Returns the height of the tree.
		 *
		 */
		uint32 GetHeight() { return GetHeight(Root); }

		/**
		 *
		 * The real GetHeight function, this function calculates the height of the tree and returns it.
		 *
		 * @param node The node, from which the height of the tree should be calculated.
		 * @return Returns the height of the tree.
		 */
		uint32 GetHeight(Node *node)
			{
			if (node == nullptr)
				return 0;

			return node->CalcHeight();
			}

		/**
		 *
		 * Helper function which should output the tree to the console by using the LevelOrder algorithm.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real LevelOrder(Node*) function with the Root node.
		 *
		 */
		void LevelOrder() { LevelOrder(Root); }

		/**
		 *
		 * Prints the tree to the console by using the LevelOrder algorithm.
		 *
		 * @param node The node, from which the tree should be printed to the console.
		 *
		 */
		void LevelOrder(Node *node)
			{
			if (node == nullptr)
				return;

			FakeQueue<Node*> q;
			q.Enqueue(node);

			while (!q.IsEmpty())
				{
				Node *current = q.Front();
				std::cout << current->Value << std::endl;

				if (current->Left)
					q.Enqueue(current->Left);

				if (current->Right)
					q.Enqueue(current->Right);

				q.Dequeue();
				}
			}

		/**
		 *
		 * Helper function which should output the tree to the console by using the PreOrder algorithm.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real PreOrder(Node*) function with the Root node.
		 *
		 */
		void PreOrder() { PreOrder(Root); }

		/**
		 *
		 * Prints the tree to the console by using the PreOrder algorithm.
		 *
		 * @param node The node, from which the tree should be printed to the console.
		 *
		 */
		void PreOrder(Node *node)
			{
			if (node == nullptr)
				return;

			std::cout << node->Value << std::endl;
			PreOrder(node->Left);
			PreOrder(node->Right);
			}

		/**
		 *
		 * Helper function which should output the tree to the console by using the InOrder algorithm.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real InOrder(Node*) function with the Root node.
		 *
		 */
		void InOrder() { InOrder(Root); }

		/**
		 *
		 * Prints the tree to the console by using the InOrder algorithm.
		 *
		 * @param node The node, from which the tree should be printed to the console.
		 *
		 */
		void InOrder(Node *node)
			{
			if (node == nullptr)
				return;

			InOrder(node->Left);
			std::cout << node->Value << std::endl;
			InOrder(node->Right);
			}

		/**
		 *
		 * Helper function which should output the tree to the console by using the PostOrder algorithm.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real PostOrder(Node*) function with the Root node.
		 *
		 */
		void PostOrder() { PostOrder(Root); }

		/**
		 *
		 * Prints the tree to the console by using the PostOrder algorithm.
		 *
		 * @param node The node, from which the tree should be printed to the console.
		 *
		 */
		void PostOrder(Node *node)
			{
			if (node == nullptr)
				return;

			PostOrder(node->Left);
			PostOrder(node->Right);
			std::cout << node->Value << std::endl;
			}
	};

typedef FakeBinaryTree<int> FakeBinaryTreeInt;
typedef FakeBinaryTree<double> FakeBinaryTreeDouble;
typedef FakeBinaryTree<float> FakeBinaryTreeFloat;
typedef FakeBinaryTree<const char *> FakeBinaryTreeString;
typedef FakeBinaryTree<short> FakeBinaryTreeShort;
typedef FakeBinaryTree<long> FakeBinaryTreeLong;
typedef FakeBinaryTree<bool> FakeBinaryTreeBool;

