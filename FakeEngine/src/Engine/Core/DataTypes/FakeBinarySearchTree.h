/*****************************************************************
 * \file   FakeBinarySearchTree.h
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
 * The BinarySearchTree implementation is meant for Clients. They can use this class to for example store their vertices in a BST.
 * This class could be helpful in loading Vertices from an FBX file as well.
 *
 */
template<typename T>
class FAKE_API FakeBinarySearchTree
	{
	private:

		struct Node
			{
			T Value;
			Node *Left, *Right;
			Node(T value) : Value(value), Left(nullptr), Right(nullptr) {}

			/**
			 *
			 * Calculates the Height of the current BST. A height is determined by the amount of levels a BST has.
			 *
			 * @return Returns the height of the current BST instance.
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
		 * Swaps both childrent of a given node, the left node will become the right node and the right node will become the left node.
		 *
		 * @param node The node which children should be swapped.
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
		FakeBinarySearchTree()
			{
			Length = 0;
			Root = nullptr;
			}

		/**
		 *
		 * Destructor removes all nodes from the bst to not leak any memory and resets the Length to 0.
		 *
		 */
		~FakeBinarySearchTree()
			{
			RemoveAll();
			Length = 0;
			}

		/**
		 *
		 * Appends a value to the BinarySearchTree.
		 *
		 * @param value The value which should be added to the tree.
		 */
		void Append(T value)
			{
			Node *node = new Node(value);
			Node *child, *parent = nullptr;
			++Length;

			child = Root;
			while (child != nullptr)
				{
				parent = child;

				if (node->Value == child->Value)
					{
					break;
					}
				else if (node->Value < child->Value)
					{
					child = child->Left;
					}
				else
					{
					child = child->Right;
					}
				}

			if (parent == nullptr)
				{
				Root = node;
				}
			else if (node->Value < parent->Value)
				{
				parent->Left = node;
				}
			else
				{
				parent->Right = node;
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
		 * The real RemoveAll function, this function removes all nodes from the BST.
		 *
		 * @param node The node, from which the tree should be freed.
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
		 */
		Node *Remove(T value) { return Remove(Root, value); } // TODO: if Root gets removed program crashes

		/**
		 *
		 * The real Remove function, this function removes a particular value and it's node from the BST.
		 *
		 * @param node The node, from which the algorithm should search for the value to delete.
		 * @param value The value, which should be searched for, to delete it from the tree.
		 * @return Returns the Node with the value which was deleted from the tree.
		 */
		Node *Remove(Node *node, T value)
			{
			if (!node)
				return nullptr;

			if (value < node->Value)
				{
				node->Left = Remove(node->Left, value);
				}
			else if (value > node->Value)
				{
				node->Right = Remove(node->Right, value);
				}
			else
				{
				if (!node->Left)
					{
					// Node with only right child
					--Length;
					Node *temp = node->Right;
					delete node;
					return temp;
					}
				else if (!node->Right)
					{
					// Node with only left child
					--Length;
					Node *temp = node->Left;
					delete node;
					return temp;
					}

				Node *inorderSuccessor = FindMinNode(node->Right);
				node->Value = inorderSuccessor->Value;
				node->Right = Remove(node->Right, inorderSuccessor->Value);
				}

			return node;
			}

		/**
		 *
		 * Helper function which should find the lowest value in the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real FindMin(Node*) function with the Root node.
		 *
		 * @return Returns the lowest value found in the tree.
		 */
		T FindMin() { return FindMin(Root); }

		/**
		 *
		 * The real FindMin function, this function finds the lowest value placed in the tree and returns it.
		 *
		 * @param node The node, from which the lowest value should be found.
		 * @return Returns the lowest value found in the tree.
		 */
		T FindMin(Node *node)
			{
			Node *current = node;
			while (current->Left)
				{
				current = current->Left;
				}

			return current->Value;
			}

		/**
		 *
		 * Helper function which should find the highest value in the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real FindMax(Node*) function with the Root node.
		 *
		 * @return Returns the highest value found in the tree.
		 */
		T FindMax() { return FindMax(Root); }

		/**
		 *
		 * The real FindMax function, this function finds the highest value placed in the tree and returns it.
		 *
		 * @param node The node, from which the highest value should be found.
		 * @return Returns the highest value found in the tree.
		 */
		T FindMax(Node *node)
			{
			Node *current = node;
			while (current->Right)
				{
				current = current->Right;
				}

			return current->Value;
			}

		/**
		 *
		 * Helper function which should find the node with the lowest value in the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real FindMinNode(Node*) function with the Root node.
		 *
		 * @return Returns the node with the lowest value.
		 */
		Node *FindMinNode() { return FindMinNode(Root); }

		/**
		 *
		 * The real FindMinNode function, this function finds the node with the lowest value placed in the tree and returns it.
		 *
		 * @param node The node, from which the node with the lowest value should be found.
		 * @return Returns the node with the lowest value.
		 */
		Node *FindMinNode(Node *node)
			{
			Node *current = node;
			while (current->Left)
				{
				current = current->Left;
				}

			return current;
			}

		/**
		 *
		 * Helper function which should find the node with the highest value in the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real FindMaxNode(Node*) function with the Root node.
		 *
		 * @return Returns the node with the highest value.
		 */
		Node *FindMaxNode() { return FindMaxNode(Root); }

		/**
		 *
		 * The real FindMaxNode function, this function finds the node with the highest value placed in the tree and returns it.
		 *
		 * @param node The node, from which the node with the highest value should be found.
		 * @return Returns the node with the highest value.
		 */
		Node *FindMaxNode(Node *node)
			{
			Node *current = node;
			while (current->Right)
				{
				current = current->Right;
				}

			return current;
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
		 */
		void Invert(Node *node)
			{
			if (!node)
				return;

			Swap(node);
			Invert(node->Left);
			Invert(node->Right);
			}

		/**
		 *
		 * Helper function which should calculate the height of the tree.
		 *
		 * This function exists so the user does not have to call this function with a particular node,
		 * because this helper function will call the real GetHeight(Node*) function with the Root node.
		 *
		 * @return Returns the height of the tree.
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
		 * Checks, if the tree is empty or not.
		 *
		 * @return Returns true if the Tree does not have any node.
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
		 */
		uint32 Size()
			{
			return Length;
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
		 */
		void LevelOrder(Node *node)
			{
			FakeQueue<Node *> q;
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

typedef FakeBinarySearchTree<int> FakeBinarySearchTreeInt;
typedef FakeBinarySearchTree<double> FakeBinarySearchTreeDouble;
typedef FakeBinarySearchTree<float> FakeBinarySearchTreeFloat;
typedef FakeBinarySearchTree<const char *> FakeBinarySearchTreeString;
typedef FakeBinarySearchTree<short> FakeBinarySearchTreeShort;
typedef FakeBinarySearchTree<long> FakeBinarySearchTreeLong;
typedef FakeBinarySearchTree<bool> FakeBinarySearchTreeBool;

