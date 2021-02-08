/*****************************************************************
 * \file   FakeMessage.h
 * \brief  
 * 
 * \author Can Karka
 * \date   February 2021
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

template<typename T>
struct FakeMessageHeader
	{
	T ID{};
	uint32 Size = 0;
	};

template<typename T>
struct FakeMessage
	{
	FakeMessageHeader<T> Header{};
	std::vector<uint8> Body;

	size_t Size() const
		{
		return Body.size();
		}

	template<typename DataType>
	friend FakeMessage<T> &operator<<(FakeMessage<T> &msg, const DataType &data)
		{
		static_assert(std::is_standard_layout<DataType>::value, "Data is too complex");
		size_t size = msg.Body.size();

		msg.Body.resize(msg.Body.size() + sizeof(DataType));
		std::memcpy(msg.Body.data() + size, &data, sizeof(DataType));

		msg.Header.Size = (uint32)msg.Size();
		return msg;
		}

	template<typename DataType>
	friend FakeMessage<T> &operator>>(FakeMessage<T> &msg, DataType &data)
		{
		static_assert(std::is_standard_layout<DataType>::value, "Data is too complex");
		size_t size = msg.Body.size() - sizeof(DataType);

		std::memcpy(&data, msg.Body.data() + size, sizeof(DataType));
		msg.Body.resize(size);

		msg.Header.Size = (uint32)msg.Size();
		return msg;
		}

	friend std::ostream &operator<<(std::ostream &stream, const FakeMessage<T> &msg)
		{
		stream << "ID: " << int32(msg.Header.ID) << ", Size: " << msg.Header.Size;
		return stream;
		}
	};


template<typename T>
class FakeConnection;

template<typename T>
struct FakeOwnedMessage
	{
	std::shared_ptr<FakeConnection<T>> Remote = nullptr;
	FakeMessage<T> Message;

	friend std::ostream &operator<<(std::ostream &stream, const FakeOwnedMessage<T> &msg)
		{
		stream << msg;
		return stream;
		}
	};
