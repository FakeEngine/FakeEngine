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

class FakeString
	{
	private:
		char *Data = 0;
		uint32 Size = 0;
		unsigned long Hash = 0;

		/**
		 *
		 * Creates a Hash of the Strings content.
		 *
		 * @warning If there is another string with the same value the hashes are going to be equal! That should be fixed soon in order to use it for the ECS.
		 *
		 */
		void CreateHash();

	public:

		static const uint32 NPOS = static_cast<uint32>(-1);

		/**
		 *
		 * default constructor.
		 *
		 */
		FakeString() = default;

		/**
		 *
		 * copies the content of the char* to the String class.
		 *
		 * @param str The string which should be stored inside the String class.
		 */
		FakeString(const char *str);

		/**
		 * 
		 * copies the content of the wchar* to the string class.
		 * 
		 * @param str The string which should be stored inside the String class.
		 */
		FakeString(const wchar_t *str);

		/**
		 *
		 * copy constructor.
		 *
		 * @param other The String which should be copied.
		 */
		FakeString(const FakeString &other);

		/**
		 *
		 * copies a string until length.
		 *
		 * @param other The String which should be copied.
		 * @param length The Length of the String to copy.
		 */
		FakeString(const FakeString &other, uint32 length);

		/**
		 *
		 * constructor for the std::string, to provide compability.
		 *
		 * @param str The std::string that should be copied.
		 */
		FakeString(const std::string &str);

		/**
		 *
		 * constructor that only copies a subpart of a string.
		 *
		 * @param other The base string from which the content should be copied.
		 * @param start The start position from where the string should be copied.
		 * @param end The end position until where the string should be copied.
		 */
		FakeString(const FakeString &other, uint32 start, uint32 end);

		/**
		 *
		 * move constructor.
		 *
		 * @param other The String that should be moved.
		 */
		FakeString(FakeString &&other) noexcept;

		/**
		 *
		 * destructor that destroy the content of the string.
		 *
		 */
		~FakeString();

		/**
		 *
		 * copy operator.
		 *
		 * @param other The String that should be copied.
		 * @return Returns the string with the new string content.
		 */
		FakeString &operator=(const FakeString &other);

		/**
		 *
		 * move operator.
		 *
		 * @param other The String that should be moved.
		 * @return Returns the string with the new string content.
		 */
		FakeString &operator=(FakeString &&other) noexcept;

		/**
		 *
		 * Allocates space on the heap to use the string afterwards.
		 *
		 * @param size The size that should be allocated on the heap.
		 */
		void Resize(int64 size);

		/**
		 *
		 * Returns the string converted to a wide string.
		 *
		 * @return Returns the string converted to a wide string.
		 */
		wchar_t *W_Str();

		/**
		 *
		 * Returns the string converted to a wide string.
		 *
		 * @return Returns the string converted to a wide string.
		 */
		const wchar_t *W_Str() const;

		/**
		 *
		 * Returns the string converted to a char*.
		 *
		 * @return Returns the string converted to a char*.
		 */
		char *C_Str();

		/**
		 *
		 * Returns the string converted to a char*.
		 *
		 * @return Returns the string converted to a char*.
		 */
		const char *C_Str() const;

		/**
		 *
		 * Returns the current size of the string.
		 *
		 * @return Returns the current size of the string.
		 */
		uint32 Length() const;

		/**
		 *
		 * Returns the Hash of the string.
		 *
		 * @return Returns the Hash of the string
		 */
		unsigned long GetHash() const;

		/**
		 *
		 * Returns the letter at the specified index.
		 *
		 * @param i The index that specified which letter to return.
		 * @return Returns the letter at the specified index.
		 */
		char At(uint32 i);

		/**
		 *
		 * Returns the letter at the specified index.
		 *
		 * @param i The index that specified which letter to return.
		 * @return Returns the letter at the specified index.
		 */
		const char At(uint32 i) const;

		/**
		 *
		 * Appends a letter to the current string.
		 *
		 * @param letter The letter that should be added to the string.
		 * @return Returns the current string with the new letter already appended.
		 */
		FakeString &Append(const char letter);

		/**
		 *
		 * Appends another string to the current string.
		 *
		 * @param other The string that should be added to the current string.
		 * @return Returns the current string with the new string already appended.
		 */
		FakeString &Append(const FakeString &other);

		/**
		 *
		 * Removes a letter from the current string.
		 *
		 * @param letter The letter that should be removed.
		 * @return Returns the current string but the letter is already removed.
		 */
		FakeString &Remove(const char letter);

		/**
		 *
		 * Removes another string from the current string.
		 *
		 * @param other The string that should be removed.
		 * @return Returns the current string but the other string is removed.
		 */
		FakeString &Remove(const FakeString &other);

		/**
		 *
		 * Finds the first position of the letter in the current string and returns it.
		 *
		 * @param letter The letter which position should be found.
		 * @return Returns the first position of the letter in the string.
		 */
		uint32 FirstIndexOf(const char letter);

		/**
		 *
		 * Finds the first position of the letter in the current string and returns it.
		 *
		 * @param letter The letter which position should be found.
		 * @return Returns the first position of the letter in the string.
		 */
		uint32 FirstIndexOf(const char letter) const;

		/**
		 *
		 * Finds the first position of the string in the current string and returns it.
		 *
		 * @param other The string which position should be found.
		 * @param offset With the offset you can skip a fixed amount of letters.
		 * @return Returns the first position of the other string in the current string instance.
		 */
		uint32 FirstIndexOf(const FakeString &other, uint32 offset = 0);

		/**
		 *
		 * Finds the first position of the string in the current string and returns it.
		 *
		 * @param other The string which position should be found.
		 * @param offset With the offset you can skip a fixed amount of letters.
		 * @return Returns the first position of the other string in the current string instance.
		 */
		uint32 FirstIndexOf(const FakeString &other, uint32 offset = 0) const;

		/**
		 *
		 * Finds the position of the letter in the current string and returns it.
		 *
		 * @param letter the letter which position should be found.
		 * @param offset With the offset you can skip a fixed amount of letters.
		 * @return Returns the position of the letter in the current string.
		 */
		uint32 IndexOf(const char letter, uint32 offset = 0);

		/**
		 *
		 * Finds the position of the letter in the current string and returns it.
		 *
		 * @param letter the letter which position should be found.
		 * @param offset With the offset you can skip a fixed amount of letters.
		 * @return Returns the position of the letter in the current string.
		 */
		uint32 IndexOf(const char letter, uint32 offset = 0) const;

		/**
		 *
		 * Finds the position of the string in the current string and returns it.
		 *
		 * @param other The string which position should be found.
		 * @param offset With the offset you can skip a fixed amount of strings.
		 * @return Returns the position of the string in the current string instance.
		 */
		uint32 IndexOf(const FakeString &other, uint32 offset = 0);

		/**
		 *
		 * Finds the position of the string in the current string and returns it.
		 *
		 * @param other The string which position should be found.
		 * @param offset With the offset you can skip a fixed amount of strings.
		 * @return Returns the position of the string in the current string instance.
		 */
		uint32 IndexOf(const FakeString &other, uint32 offset = 0) const;

		/**
		 *
		 * Finds the last position of the letter in the current string and returns it.
		 *
		 * @param letter The letter which position should be found.
		 * @return Returns the last position of the letter in the string.
		 */
		uint32 LastIndexOf(const char letter);

		/**
		 *
		 * Finds the last position of the letter in the current string and returns it.
		 *
		 * @param letter The letter which position should be found.
		 * @return Returns the last position of the letter in the string.
		 */
		uint32 LastIndexOf(const char letter) const;

		/**
		 *
		 * Finds the last position of the string in the current string and returns it.
		 *
		 * @param other The string which position should be found.
		 * @return Returns the last position of the string in the current string instance.
		 */
		uint32 LastIndexOf(const FakeString &other);

		/**
		 *
		 * Finds the last position of the string in the current string and returns it.
		 *
		 * @param other The string which position should be found.
		 * @return Returns the last position of the string in the current string instance.
		 */
		uint32 LastIndexOf(const FakeString &other) const;

		/**
		 *
		 * Searches the string for the first character that does not match any of the characters specified in its arguments.
		 *
		 * @param other Another string with the set of characters to be used in the search.
		 * @param offset Position of the first character in the string to be considered in the search.
		 * @return The position of the first character that does not match.
		 */
		uint32 FirstIndexNotOf(const FakeString &other, uint32 offset = 0);

		/**
		 *
		 * Searches the string for the first character that does not match any of the characters specified in its arguments.
		 *
		 * @param other Another string with the set of characters to be used in the search.
		 * @param offset Position of the first character in the string to be considered in the search.
		 * @return The position of the first character that does not match.
		 */
		uint32 FirstIndexNotOf(const FakeString &other, uint32 offset = 0) const;

		/**
		 *
		 * Splits the string into chunks of words by the delimiter.
		 *
		 * @param delimiter The delimiter by what the string should be splitted apart.
		 * @return Returns a vector with the splitted string as it's content.
		 */
		std::vector<FakeString> Split(char delimiter);

		/**
		 *
		 * Splits the string into chunks of words by the delimiter.
		 *
		 * @param delimiter The delimiter by what the string should be splitted apart.
		 * @param outWordCount The size of the array is being stored inside this parameter.
		 * @return Returns a array of Strings with the splitted string as it's content.
		 */
		FakeString *Split(char delimiter, uint32 *outWordCount);

		/**
		 *
		 * Works like any substring function, you can specify either a start and end position or you can just specify a start position.
		 * In case of just specifying the start position the function will set the end of the string as the end position.
		 *
		 * @param beginIndex The start position from where the string should be splitted.
		 * @param endIndex The end position until where the string should be splitted.
		 * @return Returns the sub part of the string.
		 */
		FakeString Substr(uint32 beginIndex, uint32 endIndex = 0);

		/**
		 *
		 * Works like any substring function, you can specify either a start and end position or you can just specify a start position.
		 * In case of just specifying the start position the function will set the end of the string as the end position.
		 *
		 * @param beginIndex The start position from where the string should be splitted.
		 * @param endIndex The end position until where the string should be splitted.
		 * @return Returns the sub part of the string.
		 */
		FakeString Substr(uint32 beginIndex, uint32 endIndex = 0) const;

		/**
		 *
		 * This function checks if a certain letter exists in the string.
		 *
		 * @param letter The letter which should be searched for in the string.
		 * @param offset With the offset you can skip letters, which were also found.
		 * @return Returns true if the letter was found in the string.
		 */
		bool Contains(const char letter, uint32 offset = 0);

		/**
		 *
		 * This function checks if a certain letter exists in the string.
		 *
		 * @param letter The letter which should be searched for in the string.
		 * @param offset With the offset you can skip letters, which were also found.
		 * @return Returns true if the letter was found in the string.
		 */
		bool Contains(const char letter, uint32 offset = 0) const;

		/**
		 *
		 * This function checks if a certain string exists in the current string instance.
		 *
		 * @param other The string that should be searched for in the current string instance.
		 * @param offset With the offset you can skip words, which were also found.
		 * @return Returns true if the string was found in the current string instance.
		 */
		bool Contains(const FakeString &other, uint32 offset = 0);

		/**
		 *
		 * This function checks if a certain string exists in the current string instance.
		 *
		 * @param other The string that should be searched for in the current string instance.
		 * @param offset With the offset you can skip words, which were also found.
		 * @return Returns true if the string was found in the current string instance.
		 */
		bool Contains(const FakeString &other, uint32 offset = 0) const;

		/**
		 *
		 * Finds a letter in the string and returns it's position in the string.
		 *
		 * @param letter The letter that should be found.
		 * @param offset With the offset you can skip letters, that were found too.
		 * @return Returns the position of the letter in the string.
		 */
		uint32 Find(const char letter, uint32 offset = 0) const noexcept;

		/**
		 *
		 * Finds a substring and returns it's position in the string.
		 *
		 * @param other The string that should be found.
		 * @param offset With the offset you can skip words, that were found too.
		 * @return Returns the position of the substring in the string.
		 */
		uint32 Find(const FakeString &other, uint32 offset = 0) const noexcept;

		/**
		 *
		 * Replaces a sub part of the current string instance with another string.
		 *
		 * @param find The substring that should be replaced.
		 * @param replaceValue The string that should replace the first parameter.
		 * @param occurencesToReplace The number of occurences to replace.
		 * @return Returns the current string instance, but the string contents are already replaced.
		 */
		FakeString &Replace(const FakeString &find, const FakeString &replaceValue, uint32 occurencesToReplace = 0);

		/**
		 *
		 * Converts the current string instance in only lowercase letters.
		 *
		 * @return Returns the current string instance converted to lowercase letters.
		 */
		FakeString &ToLowerCase();

		/**
		 *
		 * Converts the current string instance in only lowercase letters.
		 *
		 * @return Returns the current string instance converted to lowercase letters.
		 */
		const FakeString &ToLowerCase() const;

		/**
		 *
		 * Converts the current string instance in only uppercase letters.
		 *
		 * @return Returns the current string instance converted to uppercase letters.
		 */
		FakeString &ToUpperCase();

		/**
		 *
		 * Converts the current string instance in only uppercase letters.
		 *
		 * @return Returns the current string instance converted to uppercase letters.
		 */
		const FakeString &ToUpperCase() const;

		/**
		 *
		 * Returns the current string instance but in reversed order.
		 *
		 * @return Returns the current string instance but in reversed order.
		 */
		FakeString &Reverse();

		/**
		 *
		 * Prints the current string to the console.
		 *
		 */
		void Print();

		/**
		 *
		 * Prints the current string to the console.
		 *
		 */
		void Print() const;

		/**
		 *
		 * Check if the string has any content.
		 *
		 * @return Returns true if the current String is a empty String.
		 */
		bool IsEmpty();

		/**
		 *
		 * Check if the string has any content.
		 *
		 * @return Returns true if the current String is a empty String.
		 */
		bool IsEmpty() const;

		/**
		 *
		 * Checks if the string starts with the specified letter.
		 *
		 * @return Returns true if the current string starts with the provided string.
		 */
		bool StartsWith(const char letter);

		/**
		 *
		 * Checks if the string starts with the specified letter.
		 *
		 * @return Returns true if the current string starts with the provided string.
		 */
		bool StartsWith(const char letter) const;

		/**
		 *
		 * Checks if the string starts with the specified string.
		 *
		 * @return Returns true if the current string starts with the provided string.
		 */
		bool StartsWith(const FakeString &other);

		/**
		 *
		 * Checks if the string starts with the specified string.
		 *
		 * @return Returns true if the current string starts with the provided string.
		 */
		bool StartsWith(const FakeString &other) const;

		/**
		 *
		 * Checks if the string ends with the specified letter.
		 *
		 * @return Returns true if the current string ends with the provided string.
		 */
		bool EndsWith(const char letter);

		/**
		 *
		 * Checks if the string ends with the specified letter.
		 *
		 * @return Returns true if the current string ends with the provided string.
		 */
		bool EndsWith(const char letter) const;

		/**
		 *
		 * Checks if the string ends with the specified string.
		 *
		 * @return Returns true if the current string ends with the provided string.
		 */
		bool EndsWith(const FakeString &other);

		/**
		 *
		 * Checks if the string ends with the specified string.
		 *
		 * @return Returns true if the current string ends with the provided string.
		 */
		bool EndsWith(const FakeString &other) const;

		/**
		 *
		 * Overloaded dereferencing operator that returns the content from the string as a char*.
		 *
		 * @return Returns the content from the string as a char*.
		 */
		char *operator*();

		/**
		 *
		 * Overloaded dereferencing operator that returns the content from the string as a char*.
		 *
		 * @return Returns the content from the string as a char*.
		 */
		const char *operator*() const;

		/**
		 *
		 * Overloaded char* operator that returns the content of the string.
		 *
		 * @return Returns the content from the string as a char*.
		 */
		operator char*();

		/**
		 *
		 * Overloaded char* operator that returns the content of the string.
		 *
		 * @return Returns the content from the string as a char*.
		 */
		operator const char*() const;

		/**
		 *
		 * Checks if the current string instance equals the specified string.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the string equals the specified string.
		 */
		bool operator==(const char *other);

		/**
		 *
		 * Checks if the current string instance equals the specified string.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the string equals the specified string.
		 */
		bool operator==(const char *other) const;

		/**
		 *
		 * Checks if the current string instance equals the specified string.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the string equals the specified string.
		 */
		bool operator==(const FakeString &other);

		/**
		 *
		 * Checks if the current string instance equals the specified string.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the string equals the specified string.
		 */
		bool operator==(const FakeString &other) const;

		/**
		 *
		 * Checks if the current string instance equals not the specified string.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the string does not equal the specified string.
		 */
		bool operator!=(const char *other);

		/**
		 *
		 * Checks if the current string instance equals not the specified string.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the string does not equal the specified string.
		 */
		bool operator!=(const char *other) const;

		/**
		 *
		 * Checks if the current string instance equals not the specified string.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the string does not equal the specified string.
		 */
		bool operator!=(const FakeString &other);

		/**
		 *
		 * Checks if the current string instance equals not the specified string.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the string does not equal the specified string.
		 */
		bool operator!=(const FakeString &other) const;

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is less than the size of the specified parameter.
		 */
		bool operator<(const char *other);

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is less than the size of the specified parameter.
		 */
		bool operator<(const char *other) const;

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is less than the size of the specified parameter.
		 */
		bool operator<(const FakeString &other);

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is less than the size of the specified parameter.
		 */
		bool operator<(const FakeString &other) const;

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is greater than the size of the specified parameter.
		 */
		bool operator>(const char *other);

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is greater than the size of the specified parameter.
		 */
		bool operator>(const char *other) const;

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is greater than the size of the specified parameter.
		 */
		bool operator>(const FakeString &other);

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is greater than the size of the specified parameter.
		 */
		bool operator>(const FakeString &other) const;

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is less or equal to the size of the specified parameter.
		 */
		bool operator<=(const char *other);

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is less or equal to the size of the specified parameter.
		 */
		bool operator<=(const char *other) const;

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is less or equal to the size of the specified parameter.
		 */
		bool operator<=(const FakeString &other);

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is less or equal to the size of the specified parameter.
		 */
		bool operator<=(const FakeString &other) const;

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is greater or equal to the size of the specified parameter.
		 */
		bool operator>=(const char *other);

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is greater or equal to the size of the specified parameter.
		 */
		bool operator>=(const char *other) const;

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is greater or equal to the size of the specified parameter.
		 */
		bool operator>=(const FakeString &other);

		/**
		 *
		 * Checks the size of the specified string and the size of the current string instance.
		 *
		 * @param other The string that should be compared with.
		 * @return Returns true if the size of the current string instance is greater or equal to the size of the specified parameter.
		 */
		bool operator>=(const FakeString &other) const;

		/**
		 *
		 * Overloaded - operator that calls the Remove(const FakeString&) function.
		 *
		 * @param str The string that should be modified.
		 * @param other The string that should be removed.
		 * @return Returns the first parameter but without the second parameter.
		 */
		friend FakeString operator-(FakeString str, const FakeString &other);

		/**
		 *
		 * Overloaded - operator that calls the Remove(const char) function.
		 *
		 * @param str The string that should be modified.
		 * @param letter The letter that should be removed.
		 * @return Returns the first parameter but without the second parameter.
		 */
		friend FakeString operator-(FakeString str, const char letter);

		/**
		 *
		 * Overloaded -= operator that calls the Remove(const FakeString&) function.
		 *
		 * @param other The string that should be removed.
		 * @return Returns the current string instance but without the first parameter.
		 */
		FakeString &operator-=(const FakeString &other);

		/**
		 *
		 * Overloaded -= operator that calls the Remove(const char) function.
		 *
		 * @param letter The letter that should be removed.
		 * @return Returns the current string instance but without the first parameter.
		 */
		FakeString &operator-=(const char letter);

		/**
		 *
		 * Overloaded + operator that calls the Append(const FakeString&) function.
		 *
		 * @param str The string that should be modified.
		 * @param other The string that should be added.
		 * @return Returns the first parameter but with the second parameter added.
		 */
		friend FakeString operator+(FakeString str, const FakeString &other);

		/**
		 *
		 * Overloaded + operator that calls the Append(const char) function.
		 *
		 * @param str The string that should be modified.
		 * @param letter The letter that should be added.
		 * @return Returns the first parameter but with the second parameter added.
		 */
		friend FakeString operator+(FakeString str, const char letter);

		/**
		 *
		 * Overloaded += operator that calls the Append(const FakeString&) function.
		 *
		 * @param other The string that should be added.
		 * @return Returns the current string instance but with the parameter added.
		 */
		FakeString &operator+=(const FakeString &other);

		/**
		 *
		 * Overloaded += operator that calls the Append(const char) function.
		 *
		 * @param letter The letter that should be added.
		 * @return Returns the current string instance but with the parameter added.
		 */
		FakeString &operator+=(const char letter);

		/**
		 *
		 * Converts any value to a string.
		 *
		 * @param value The value that should be converted to a string
		 * @return Returns a new string with the specified value.
		 */
		template<typename T>
		static FakeString ToString(const T &value)
			{
			std::stringstream ss;
			ss << value;
			return FakeString(ss.str());
			}

		/**
		 *
		 * Returns the letter at the specified index.
		 *
		 * @param i The position in the string that should be returned.
		 * @return Returns the letter at the specified index.
		 */
		char &operator[](uint32 i);

		/**
		 *
		 * Returns the letter at the specified index.
		 *
		 * @param i The position in the string that should be returned.
		 * @return Returns the letter at the specified index.
		 */
		const char &operator[](uint32 i) const;

		/**
		 *
		 * Writes the hole string into the output stream.
		 *
		 * @param stream The stream, which should be filled with the content of the string.
		 * @param string The string, which should be written to the stream.
		 * @return Returns the stream, which was filled with the content of the string.
		 */
		friend std::ostream &operator<<(std::ostream &stream, const FakeString &string);
	};
