/*****************************************************************
 * \file   FakeHashFunctions.h
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
 * .
 * 
 * @param key
 * @return 
 */
inline int32 fake_get_hash(const uint8 key)
	{
	return key;
	}

/**
 * 
 * .
 * 
 * @param key
 * @return 
 */
inline uint32 fake_get_hash(const uint16 key)
	{
	return key;
	}

/**
 * 
 * .
 * 
 * @param key
 * @return 
 */
inline uint32 fake_get_hash(const int16 key)
	{
	return key;
	}

/**
 * 
 * .
 * 
 * @param key
 * @return 
 */
inline uint32 fake_get_hash(const int32 key)
	{
	return key;
	}

/**
 * 
 * .
 * 
 * @param key
 * @return 
 */
inline uint32 fake_get_hash(const uint32 key)
	{
	return key;
	}

/**
 * 
 * .
 * 
 * @param key
 * @return 
 */
inline uint32 fake_get_hash(const uint64 key)
	{
	return (uint32)key + ((uint32)(key >> 32) * 23);
	}

/**
 * 
 * .
 * 
 * @param key
 * @return 
 */
inline uint32 fake_get_hash(const int64 key)
	{
	return (uint32)key + ((uint32)(key >> 32) * 23);
	}

/**
 * 
 * .
 * 
 * @param key
 * @return 
 */
inline uint32 fake_get_hash(const char key)
	{
	return key;
	}

/**
 * 
 * .
 * 
 * @param key
 * @return 
 */
inline uint32 fake_get_hash(const float key)
	{
	return *(uint32*) &key;
	}

/**
 * 
 * .
 * 
 * @param key
 * @return 
 */
inline uint32 fake_get_hash(const double key)
	{
	return fake_get_hash(*(uint64*) &key);
	}

/**
 * 
 * .
 * 
 * @param key
 * @return 
 */
inline uint32 fake_get_hash(const void *key)
	{
	static const int64 shift = 3;
	return (uint32)((int64)(key) >> shift);
	}

/**
 * 
 * .
 * 
 * @param key
 * @return 
 */
inline uint32 fake_get_hash(void *key)
	{
	static const int64 shift = 3;
	return (uint32)((int64)(key) >> shift);
	}

/**
 * 
 * .
 * 
 * @param hash
 * @param value
 */
inline void fake_combine_hash(uint32 &hash, const uint32 value)
	{
	hash ^= value + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	}

/**
 * 
 * .
 * 
 * @param hash
 * @param value
 */
template<typename T>
inline void fake_combine_hash(uint32 &hash, const T *value)
	{
	fake_combine_hash(hash, fake_get_hash(value));
	}


