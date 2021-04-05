/*****************************************************************
 * \file   FakeString.h
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

#include <string>
#include <sstream>

/**
 * 
 * .
 * 
 */
class FakeString
	{
	private:
		char *Data = 0;
		uint32 Size = 0;
		
	public:

		static const uint32 NPOS = static_cast<uint32>(-1);

		FakeString() = default;
		FakeString(const char *data);
		FakeString(const wchar_t *data);
		FakeString(const std::string &str);
		FakeString(const std::wstring &wideStr);
		FakeString(const FakeString &other);
		FakeString(const FakeString &other, uint32 length);
		FakeString(const FakeString &other, uint32 start, uint32 end);
		FakeString(FakeString &&other) noexcept;
		~FakeString();

		FakeString &operator=(const FakeString &other);
		FakeString &operator=(FakeString &&other) noexcept;

		void Clear();
		void Resize(int64 size);
		uint32 Length() const;

		wchar_t *W_Str();
		const wchar_t *W_Str() const;

		char *C_Str();
		const char *C_Str() const;

		char At(uint32 index);
		const char At(uint32 index) const;

		FakeString &Append(const char letter);
		FakeString &Append(const FakeString &other);
		FakeString &Remove(const char letter);
		FakeString &Remove(const FakeString &other);

		uint32 FirstIndexOf(const char letter, uint32 offset = 0) const;
		uint32 FirstIndexOf(const FakeString &other, uint32 offset = 0) const;
		uint32 IndexOf(const char letter, uint32 offset = 0) const;
		uint32 IndexOf(const FakeString &other, uint32 offset = 0) const;
		uint32 LastIndexOf(const char letter, uint32 offset = 0) const;
		uint32 LastIndexOf(const FakeString &other, uint32 offset = 0) const;
		uint32 FirstIndexNotOf(const char letter, uint32 offset = 0) const;
		uint32 FirstIndexNotOf(const FakeString &other, uint32 offset = 0) const;

		std::vector<FakeString> Split(char delimiter);
		FakeString *Split(char delimiter, uint32 *outWordCount);
		FakeString &Replace(const FakeString &find, const FakeString &replaceValue, uint32 occurencesToReplace = 0);
		FakeString &Reverse();
		FakeString Substr(uint32 beginIndex, uint32 endIndex = 0) const;

		const FakeString &ToLower() const;
		const FakeString &ToUpper() const;

		void Print() const;

		bool IsEmpty() const;
		bool Contains(const char letter, uint32 offset = 0) const;
		bool Contains(const FakeString &other, uint32 offset = 0) const;
		bool StartsWith(const char letter) const;
		bool StartsWith(const FakeString &other) const;
		bool EndsWith(const char letter) const;
		bool EndsWith(const FakeString &other) const;

		char *operator*();
		const char *operator*() const;

		operator char*();
		operator const char*() const;

		bool operator==(const char *other) const;
		bool operator==(const FakeString &other) const;
		bool operator!=(const char *other) const;
		bool operator!=(const FakeString &other) const;
		bool operator<(const char *other) const;
		bool operator<(const FakeString &other) const;
		bool operator>(const char *other) const;
		bool operator>(const FakeString &other) const;
		bool operator<=(const char *other) const;
		bool operator<=(const FakeString &other) const;
		bool operator>=(const char *other) const;
		bool operator>=(const FakeString &other) const;

		friend FakeString operator-(FakeString str, const FakeString &other);
		friend FakeString operator-(FakeString str, const char letter);
		friend FakeString operator-(FakeString str, const char *other);
		friend FakeString operator+(FakeString str, const FakeString &other);
		friend FakeString operator+(FakeString str, const char letter);
		friend FakeString operator+(FakeString str, const char *other);
		FakeString &operator-=(const FakeString &other);
		FakeString &operator-=(const char letter);
		FakeString &operator+=(const FakeString &other);
		FakeString &operator+=(const char letter);

		char &operator[](uint32 index);
		const char &operator[](uint32 index) const;

		friend std::ostream &operator<<(std::ostream &stream, const FakeString &str);

		template<typename T>
		static FakeString ToString(const T &value)
			{
			std::stringstream ss;
			ss << value;
			return FakeString(ss.str());
			}

		template<typename T>
		friend FakeString &operator<<(FakeString &str, const T &value)
			{
			FakeString newStr = FakeString::ToString(value);
			return str.Append(newStr);
			}

		template<typename T>
		friend FakeString &operator>>(FakeString &str, const T &value)
			{
			FakeString newStr = FakeString::ToString(value);
			return str.Remove(newStr);
			}
	};
