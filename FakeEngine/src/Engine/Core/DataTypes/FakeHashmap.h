/*****************************************************************
 * \file   FakeHashmap.h
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

#include <vector>

#include "Engine/Core/FakeCore.h"

 /**
  *
  * A basic implementation of a Hashmap. A hashmap can be useful if you need a way to store a combination of two values.
  * The hashmap represents this by storing a key and a value which belong to each other.
  *
  */
template<typename T, typename F>
class FAKE_API FakeHashmap
	{
	private:
		std::vector<std::pair<T, F>> Elements;

	public:

		/**
		 *
		 * Empty constructor.
		 *
		 */
		FakeHashmap()
			{
			}

		/**
		 *
		 * Destructor removes all elements from the hashmap and frees the memory.
		 *
		 */
		~FakeHashmap()
			{
			Elements.clear();
			Elements.shrink_to_fit();
			}

		/**
		 *
		 * Checks if the hashmap has a particular key or not.
		 *
		 * @param key The key which should be searched for in the hashmap.
		 * @return Returns true if the key has been found in the hashmap.
		 */
		bool ContainsKey(T key)
			{
			for (auto it = Elements.begin(); it != Elements.end(); ++it)
				{
				std::pair<T, F> current = *it;
				if (current.first == key)
					return true;
				}

			return false;
			}

		/**
		 *
		 * Checks if the hashmap has a particular value or not.
		 *
		 * @param value The value which should be searched for in the hashmap.
		 * @return Returns true if the value has been found in the hashmap.
		 */
		bool ContainsValue(F value)
			{
			for (auto it = Elements.begin(); it != Elements.end(); ++it)
				{
				std::pair<T, F> current = *it;
				if (current.second == value)
					return true;
				}

			return false;
			}

		/**
		 *
		 * Creates a new element in the hashmap and stores the given key and value in that new element.
		 *
		 * @param key The key which should be stored in the hashmap.
		 * @param value The value which should be stored in the hashmap.
		 * @return Returns true if the key and the value has been stored successfully in the hashmap.
		 */
		bool Put(T key, F value) // TODO: seems not to work with the ShaderLibrary!!!
			{
			if (!ContainsKey(key) && !ContainsValue(value))
				{
				std::pair<T, F> pair;
				pair.first = key;
				pair.second = value;
				Elements.push_back(pair);
				return true;
				}

			return false;
			}

		/**
		 *
		 * Searches for the key and overrides it's value with the new value.
		 *
		 * @param key The key which should be searched for in the hashmap.
		 * @param value The value, which should replace the current value of the given key.
		 * @return Returns true if the value of the key has been successfully overriden.
		 */
		bool Set(T key, F value)
			{
			if (ContainsKey(key))
				{
				uint32 i;
				for (i = 0; i < Elements.size(); ++i)
					{
					std::pair<T, F> current = Elements.at(i);
					if (current.first == key)
						{
						Elements.at(i).second = value;
						return true;
						}
					}
				}

			return false;
			}

		/**
		 *
		 * Removes the combination of key and value from the hashmap.
		 *
		 * @param key The key that should be removed from the hashmap.
		 * @param value The value that should be removed from the hashmap.
		 * @return Returns true if the combination of key and value has been successfully removed from the hashmap.
		 */
		bool Remove(T key, F value)
			{
			if (ContainsKey(key) && ContainsValue(value))
				{
				uint32 i;
				for (i = 0; i < Elements.size(); ++i)
					{
					std::pair<T, F> current = Elements.at(i);
					if (current.first == key && current.second == value)
						{
						Elements.erase(Elements.begin() + i);
						return true;
						}
					}
				}

			return false;
			}

		/**
		 *
		 * Removes all elements from the hashmap that have the same key as specified in the parameter.
		 *
		 * @param key The key that should entirely be removed from the hashmap.
		 * @return Returns true if all keys matching the parameter has been removed successfully from the hashmap.
		 */
		bool Remove(T key)
			{
			if (ContainsKey(key))
				{
				uint32 i;
				for (i = 0; i < Elements.size(); ++i)
					{
					std::pair<T, F> current = Elements.at(i);
					if (current.first == key)
						Elements.erase(Elements.begin() + i);
					}

				return true;
				}

			return false;
			}

		/**
		 *
		 * Removes all elements from the hashmap and frees the memory afterwards.
		 *
		 */
		void RemoveAll()
			{
			Elements.clear();
			Elements.shrink_to_fit();
			}

		/**
		 *
		 * Removes the first entry in the hashmap (both, key and value).
		 *
		 */
		bool RemoveFirst()
			{
			Elements.erase(Elements.begin() + 0);
			return true;
			}

		/**
		 *
		 * Removes the last entry in the hashmap (both, key and value).
		 *
		 */
		bool RemoveLast()
			{
			Elements.erase(Elements.begin() + (Elements.size() - 1));
			return true;
			}

		/**
		 *
		 * Returns the value of the first entry in the hashmap.
		 *
		 * @return Returns the value of the first entry in the hashmap.
		 */
		F GetFirst()
			{
			return Elements.at(0).second;
			}

		/**
		 *
		 * Returns the value of the last entry in the hashmap.
		 *
		 * @return Returns the value of the last entry in the hashmap.
		 */
		F GetLast()
			{
			return Elements.at(Elements.size() - 1).second;
			}

		/**
		 *
		 * Returns the value at the specified index.
		 *
		 * @return Returns the value at the specified index.
		 */
		F GetAt(int32 i)
			{
			return Elements.at(i).second;
			}

		/**
		 *
		 * Returns the key at the specified index.
		 *
		 * @return Returns the key at the specified index
		 */
		T GetKey(int32 i)
			{
			return Elements.at(i).first;
			}

		/**
		 *
		 * Checks if the hashmap is empty or not.
		 *
		 * @return Returns true if the hashmap is empty.
		 */
		bool IsEmpty()
			{
			return Elements.size() == 0;
			}

		/**
		 *
		 * Returns the current size of the hashmap.
		 *
		 * @return Returns the current amount of entries in the hashmap.
		 */
		uint32 Size()
			{
			return (uint32)Elements.size();
			}

		/**
		 *
		 * Prints the hashmap to the console.
		 *
		 */
		void Print()
			{
			for (auto it = Elements.begin(); it != Elements.end(); it++)
				{
				std::pair<T, F> current = *it;
				std::cout << current.first << ", " << current.second << std::endl;
				}
			}

		/**
		 *
		 * Checks if a particular key is stored in the hashmap.
		 *
		 * @param key The key which should be searched for in the hashmap.
		 * @return Returns true if the specified key is present in the hashmap.
		 */
		bool HasKey(const T &key)
			{
			for (uint32 i = 0; i < Elements.size(); ++i)
				{
				std::pair<T, F> current = Elements.at(i);
				if (current.first == key)
					return true;
				}

			return false;
			}

		/**
		 *
		 * Checks if a particular key is stored in the hashmap.
		 *
		 * @param key The key which should be searched for in the hashmap.
		 * @return Returns true if the specified key is present in the hashmap.
		 */
		bool HasKey(const T &key) const
			{
			for (uint32 i = 0; i < Elements.size(); ++i)
				{
				std::pair<T, F> current = Elements.at(i);
				if (current.first == key)
					return true;
				}

			return false;
			}

		/**
		 *
		 * Returns the value at the specified key.
		 *
		 * @param key The key at which the value should be returned.
		 * @return Returns the value at the specified key.
		 */
		F &operator[](const T &key)
			{
			static F value;

			for (uint32 i = 0; i < Elements.size(); ++i)
				{
				std::pair<T, F> current = Elements.at(i);
				if (current.first == key)
					{
					value = current.second;
					break;
					}
				}

			return value;
			}

		/**
		 *
		 * Returns the value at the specified key.
		 *
		 * @param key The key at which the value should be returned.
		 * @return Returns the value at the specified key.
		 *
		 */
		const F &operator[](const T &key) const
			{
			static F value;

			for (uint32 i = 0; i < Elements.size(); ++i)
				{
				std::pair<T, F> current = Elements.at(i);
				if (current.first == key)
					{
					value = current.second;
					break;
					}
				}

			return value;
			}

		/**
		 *
		 * Returns the value at the specified index.
		 *
		 * @param i The index at which the value should be returned.
		 * @return Returns the value at the specified index.
		 *
		 */
		F &operator[](size_t i) { return Elements.at(i).second; }

		/**
		 *
		 * Returns the value at the specified index.
		 *
		 * @param i The index at which the value should be returned.
		 * @return Returns the value at the specified index.
		 *
		 */
		const F &operator[](size_t i) const { return Elements.at(i).second; }

		/**
		 *
		 * Writes the hole hashmap into the output stream.
		 *
		 * @param stream The stream, which should be filled with the content of the hashmap.
		 * @param hashmap The hashmap, which should be written to the stream.
		 * @return Returns the stream, which was filled with the content of the hashmap.
		 */
		friend std::ostream &operator<<(std::ostream &stream, FakeHashmap<T, F> &hashmap)
			{
			stream << "[" << std::endl;
			uint32 i;
			for (i = 0; i < hashmap.Size(); ++i)
				{
				std::pair<T, F> &current = hashmap[i];

				stream << "  {";
				stream << " " << current.first << ", " << current.second << " ";

				if ((i + 1) == hashmap.Size())
					stream << "}" << std::endl;
				else
					stream << "}," << std::endl;
				}
			stream << "]";

			return stream;
			}
	};

typedef FakeHashmap<const char *, int> FakeHashmapInt;
typedef FakeHashmap<const char *, float> FakeHashmapFloat;
typedef FakeHashmap<const char *, double> FakeHashmapDouble;
typedef FakeHashmap<const char *, const char *> FakeHashmapString;
typedef FakeHashmap<const char *, short> FakeHashmapShort;
typedef FakeHashmap<const char *, long> FakeHashmapLong;
typedef FakeHashmap<const char *, bool> FakeHashmapBool;

