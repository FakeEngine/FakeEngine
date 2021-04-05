#include "FakePch.h"
#include "FakeString.h"

FakeString::FakeString(const char *data)
	{
	Size = (uint32)strlen(data);
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, data, Size);
	}

FakeString::FakeString(const wchar_t *data)
	{
	Size = (uint32)wcslen(data);
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, data, Size);
	}

FakeString::FakeString(const std::string &str)
	{
	Size = (uint32)strlen(str.c_str());
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, str.c_str(), Size);
	}

FakeString::FakeString(const std::wstring &wideStr)
	{
	Size = (uint32)wcslen(wideStr.c_str());
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, wideStr.c_str(), Size);
	}

FakeString::FakeString(const FakeString &other)
	{
	Size = other.Size;
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, other.Data, Size);
	}

FakeString::FakeString(const FakeString &other, uint32 length)
	{
	Size = length;
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, other.Data, Size);
	}

FakeString::FakeString(const FakeString &other, uint32 start, uint32 end)
	{
	Size = end - start;
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, &other.Data[start], Size);
	}

FakeString::FakeString(FakeString &&other) noexcept
	{
	Size = other.Size;
	Data = other.Data;

	other.Size = 0;
	other.Data = nullptr;
	}

FakeString::~FakeString()
	{
	Size = 0;
	if (Data)
		{
		delete[] Data;
		Data = nullptr;
		}
	}

FakeString &FakeString::operator=(const FakeString &other)
	{
	if (this != &other)
		{
		if (Data)
			delete[] Data;

		Size = other.Size;
		Data = new char[Size + 1];
		Data[Size] = '\0';
		memcpy(Data, other.Data, Size);
		}

	return *this;
	}

FakeString &FakeString::operator=(FakeString &&other) noexcept
	{
	if (this != &other)
		{
		if (Data)
			delete[] Data;

		Size = other.Size;
		Data = other.Data;

		other.Size = 0;
		other.Data = nullptr;
		}

	return *this;
	}

void FakeString::Clear()
	{
	delete[] Data;
	Data = nullptr;
	Size = 0;
	}

void FakeString::Resize(int64 size)
	{
	if (Data)
		delete[] Data;

	Size = (uint32)size;
	Data = new char[Size];
	}

uint32 FakeString::Length() const
	{
	return Size;
	}

wchar_t *FakeString::W_Str()
	{
	wchar_t *result = new wchar_t[Size + 1];
	for (uint32 i = 0; i < Size; ++i)
		result[i] = Data[i];

	result[Size] = '\0';
	return result;
	}

const wchar_t *FakeString::W_Str() const
	{
	wchar_t *result = new wchar_t[Size + 1];
	for (uint32 i = 0; i < Size; ++i)
		result[i] = Data[i];

	result[Size] = '\0';
	return result;
	}

char *FakeString::C_Str()
	{
	return Data;
	}

const char *FakeString::C_Str() const
	{
	return Data;
	}

char FakeString::At(uint32 index)
	{
	if (index < Size)
		{
		return Data[index];
		}

	return (char)NPOS;
	}

const char FakeString::At(uint32 index) const
	{
	if (index < Size)
		{
		return Data[index];
		}

	return (char)NPOS;
	}

FakeString &FakeString::Append(const char letter)
	{
	char *new_data = new char[Size + 2]; // +1 for a character and another +1 for the null terminator
	new_data[Size] = letter;
	new_data[Size + 1] = '\0';

	if (Data)
		{
		memcpy(new_data, Data, Size);
		delete[] Data;
		}

	Data = new_data;
	++Size;

	return *this;
	}

FakeString &FakeString::Append(const FakeString &other)
	{
	uint32 new_size = Size + other.Size;
	char *new_data = new char[new_size + 1]; // +1 for the null terminator
	new_data[new_size] = '\0';

	if (Data)
		{
		memcpy(new_data, Data, Size); // copy existing string data
		delete[] Data;
		}

	memcpy((char *)(new_data + Size), other.Data, other.Size); // copy appended string data
	Data = new_data;
	Size = new_size;

	return *this;
	}

FakeString &FakeString::Remove(const char letter)
	{
	if (Contains(letter))
		{
		uint32 i = 0;
		uint32 j = 0;
		uint32 start_pos = IndexOf(letter);
		uint32 new_size = Size - 1;
		char *new_data = new char[new_size + 1];
		new_data[new_size] = '\0';

		if (Data)
			{
			if (start_pos > 0)
				{
				memcpy(new_data, Data, start_pos);
				j = start_pos;
				}

			for (i = start_pos + 1; i < Size; ++i)
				{
				new_data[j] = Data[i];
				++j;
				}

			delete[] Data;
			Data = new_data;
			Size = new_size;
			}
		}

	return *this;
	}

FakeString &FakeString::Remove(const FakeString &other)
	{
	if (Contains(other))
		{
		uint32 i = 0;
		uint32 j = 0;
		uint32 start_pos = IndexOf(other);
		uint32 new_size = Size - other.Length();
		char *new_data = new char[new_size + 1];
		new_data[new_size] = '\0';

		if (Data)
			{
			// copy part before the part to remove
			if (start_pos > 0)
				{
				memcpy(new_data, Data, start_pos);
				j = start_pos;
				}

			// copy part after the part to remove
			for (i = start_pos + other.Length(); i < Size; ++i)
				{
				new_data[j] = Data[i];
				++j;
				}

			delete[] Data;
			Data = new_data;
			Size = new_size;
			}
		}

	return *this;
	}

uint32 FakeString::FirstIndexOf(const char letter, uint32 offset) const
	{
	for (uint32 i = offset; i < Size; ++i)
		{
		if (Data[i] == letter)
			return i;
		}

	return NPOS;
	}

uint32 FakeString::FirstIndexOf(const FakeString &other, uint32 offset) const
	{
	uint32 i = offset;
	uint32 j = 0;

	while (Data[i] != '\0')
		{
		if (Data[i] == other[j])
			{
			while (Data[i] == other[j] && other[j] != '\0')
				{
				++j;
				++i;
				}

			if (other[j] == '\0')
				return i - j;

			j = 0;
			}

		++i;
		}

	return NPOS;
	}

uint32 FakeString::IndexOf(const char letter, uint32 offset) const
	{
	for (uint32 i = offset; i < Size; ++i)
		{
		if (Data[i] == letter)
			return i;
		}

	return NPOS;
	}

uint32 FakeString::IndexOf(const FakeString &other, uint32 offset) const
	{
	uint32 i = offset;
	uint32 j = 0;

	while (Data[i] != '\0')
		{
		if (Data[i] == other[j])
			{
			while (Data[i] == other[j] && other[j] != '\0')
				{
				++j;
				++i;
				}

			if (other[j] == '\0')
				return i - j;

			j = 0;
			}

		++i;
		}

	return NPOS;
	}

uint32 FakeString::LastIndexOf(const char letter, uint32 offset) const
	{
	// Count how many times the letter exists
	uint32 letterCount = 0;
	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == letter)
			++letterCount;
		}

	// If No Letter exists, return
	if (0 == letterCount)
		return NPOS;

	// Get the last letter index
	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == letter && letterCount > 0)
			{
			--letterCount;
			continue;
			}

		if (Data[i] == letter)
			return i;
		}

	return NPOS;
	}

uint32 FakeString::LastIndexOf(const FakeString &other, uint32 offset) const
	{
	if (Contains(other))
		{
		uint32 i = Size - other.Length();
		uint32 j = 0;

		while (Data[i] != '\0')
			{
			if (Data[i] == other[j])
				{
				while (Data[i] == other[j] && other[j] != '\0')
					{
					++j;
					++i;
					}

				if (other[j] == '\0')
					return i - j;

				j = 0;
				}

			++i;
			}

		return i;
		}

	return NPOS;
	}

uint32 FakeString::FirstIndexNotOf(const char letter, uint32 offset) const
	{
	const int len = static_cast<int>(strspn(Data + offset, &letter));
	if (len + offset >= Size)
		return NPOS;

	return len + offset;
	}

uint32 FakeString::FirstIndexNotOf(const FakeString &other, uint32 offset) const
	{
	const int len = static_cast<int>(strspn(Data + offset, *other));
	if (len + offset >= Size)
		return NPOS;

	return len + offset;
	}

std::vector<FakeString> FakeString::Split(char delimiter)
	{
	// First get the word count to construct the size of the array
	// Then iterate through the string and put every word into the array
	// Thanks to Albert Slepak (https://github.com/FlareCoding)

	uint32 wordCount = 1;
	uint32 charIdx = 0;
	uint32 wordBeginIdx = 0;
	FakeString word;

	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == delimiter)
			++wordCount;
		}

	std::vector<FakeString> result(wordCount);
	for (uint32 i = 0; i < wordCount; ++i)
		{
		wordBeginIdx = charIdx;
		while (Data[charIdx] != delimiter && Data[charIdx] != '\0')
			++charIdx;

		word = Substr(wordBeginIdx, charIdx);
		result[i] = word;
		++charIdx;
		}

	return result;
	}

FakeString *FakeString::Split(char delimiter, uint32 *outWordCount)
	{
	// First get the word count to construct the size of the array
	// Then iterate through the string and put every word into the array
	// Thanks to Albert Slepak (https://github.com/FlareCoding)

	uint32 wordCount = 1;
	uint32 charIdx = 0;
	uint32 wordBeginIdx = 0;
	FakeString word;

	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == delimiter)
			++wordCount;
		}

	FakeString *result = new FakeString[wordCount];
	for (uint32 i = 0; i < wordCount; ++i)
		{
		wordBeginIdx = charIdx;
		while (Data[charIdx] != delimiter && Data[charIdx] != '\0')
			++charIdx;

		word = Substr(wordBeginIdx, charIdx);
		result[i] = word;
		++charIdx;
		}

	if (outWordCount)
		*outWordCount = wordCount;

	return result;
	}

FakeString &FakeString::Replace(const FakeString &find, const FakeString &replaceValue, uint32 occurencesToReplace)
	{
	// Thanks to Albert Slepak (https://github.com/FlareCoding)

	uint32 occurences = 0;
	uint32 offset = 0;

	while (Contains(find, offset))
		{
		occurences++;
		offset = IndexOf(find, offset) + find.Length();

		if (occurencesToReplace && occurences == occurencesToReplace)
			break;
		}

	if (!occurences)
		return *this;

	uint32 *occurence_indices = new uint32[occurences];
	offset = 0;
	for (uint32 i = 0; i < occurences; ++i)
		{
		occurence_indices[i] = IndexOf(find, offset);
		offset = occurence_indices[i] + find.Length();
		}

	uint32 new_size = Size + ((replaceValue.Length() - find.Length()) * occurences);
	char *new_data = new char[new_size + 1];
	new_data[new_size] = '\0';

	uint32 occurence_idx = 0;
	for (uint32 dataIdx = 0, NewDataIdx = 0; dataIdx < Size;)
		{
		if (dataIdx != occurence_indices[occurence_idx])
			{
			new_data[NewDataIdx] = Data[dataIdx];
			++NewDataIdx;
			++dataIdx;
			}
		else
			{
			memcpy(new_data + NewDataIdx, replaceValue.Data, replaceValue.Length());
			NewDataIdx += replaceValue.Length();
			dataIdx += find.Length();
			++occurence_idx;
			}
		}

	if (Data)
		delete[] Data;

	Data = new_data;
	Size = new_size;
	delete[] occurence_indices;

	return *this;
	}

FakeString &FakeString::Reverse()
	{
	// Thanks to Albert Slepak (https://github.com/FlareCoding)

	for (uint32 i = 0; i < Size / 2; i++)
		{
		char temp = Data[i];
		Data[i] = Data[Size - i - 1];
		Data[Size - i - 1] = temp;
		}

	return *this;
	}

FakeString FakeString::Substr(uint32 beginIndex, uint32 endIndex) const
	{
	if (endIndex == 0)
		endIndex = Size;

	if ((endIndex - beginIndex) > Size)
		return FakeString("-1");

	return FakeString(*this, beginIndex, endIndex);
	}

const FakeString &FakeString::ToLower() const
	{
	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] >= 'A' && Data[i] <= 'Z')
			Data[i] = Data[i] - ('A' - 'a');
		}

	return *this;
	}

const FakeString &FakeString::ToUpper() const
	{
	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] >= 'a' && Data[i] <= 'z')
			Data[i] = Data[i] + ('A' - 'a');
		}

	return *this;
	}

void FakeString::Print() const
	{
	for (uint32 i = 0; i < Size; ++i)
		printf("%c", Data[i]);
	printf("\n");
	}

bool FakeString::IsEmpty() const
	{
	return Size == 0;
	}

bool FakeString::Contains(const char letter, uint32 offset) const
	{
	bool hasLetter = false;

	for (uint32 i = offset; i < Size; ++i)
		{
		if (Data[i] == letter)
			{
			hasLetter = true;
			break;
			}
		}

	return hasLetter;
	}

bool FakeString::Contains(const FakeString &other, uint32 offset) const
	{
	uint32 i = offset;
	uint32 j = 0;

	while (Data[i] != '\0')
		{
		if (Data[i] == other[j])
			{
			while (Data[i] == other[j] && other[j] != '\0')
				{
				++j;
				++i;
				}

			if (other[j] == '\0')
				return true;

			j = 0;
			}

		++i;
		}

	return false;
	}

bool FakeString::StartsWith(const char letter) const
	{
	if (Data[0] == letter)
		return true;

	return false;
	}

bool FakeString::StartsWith(const FakeString &other) const
	{
	uint32 equalCount = 0;
	for (uint32 i = 0; i < other.Size; ++i)
		{
		if (Data[i] == other[i])
			++equalCount;
		}

	if (equalCount == other.Size)
		return true;

	return false;
	}

bool FakeString::EndsWith(const char letter) const
	{
	if (Data[Size - 1] == letter)
		return true;

	return false;
	}

bool FakeString::EndsWith(const FakeString &other) const
	{
	uint32 equalCount = 0;
	uint32 start_pos = Size - other.Size;

	for (uint32 i = start_pos; i < Size; ++i)
		{
		for (uint32 j = 0; j < other.Size; ++j)
			{
			if (Data[i] == other[j])
				++equalCount;
			}
		}

	if (equalCount == other.Size)
		return true;

	return false;
	}

char *FakeString::operator*()
	{
	return Data;
	}

const char *FakeString::operator*() const
	{
	return Data;
	}

FakeString::operator char *()
	{
	return Data;
	}

FakeString::operator const char *() const
	{
	return Data;
	}

bool FakeString::operator==(const char *other) const
	{
	if (Size != strlen(other))
		return false;

	uint32 equalCount = 0;
	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == other[i])
			++equalCount;
		}

	if (equalCount == Size)
		return true;

	return false;
	}

bool FakeString::operator==(const FakeString &other) const
	{
	if (Size != other.Size)
		return false;

	uint32 equalCount = 0;
	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == other[i])
			++equalCount;
		}

	if (equalCount == Size)
		return true;

	return false;
	}

bool FakeString::operator!=(const char *other) const
	{
	return !(*this == other);
	}

bool FakeString::operator!=(const FakeString &other) const
	{
	return !(*this == other);
	}

bool FakeString::operator<(const char *other) const
	{
	return Size < strlen(other);
	}

bool FakeString::operator<(const FakeString &other) const
	{
	return Size < other.Size;
	}

bool FakeString::operator>(const char *other) const
	{
	return Size > strlen(other);
	}

bool FakeString::operator>(const FakeString &other) const
	{
	return Size > other.Size;
	}

bool FakeString::operator<=(const char *other) const
	{
	return Size <= strlen(other);
	}

bool FakeString::operator<=(const FakeString &other) const
	{
	return Size <= other.Size;
	}

bool FakeString::operator>=(const char *other) const
	{
	return Size >= strlen(other);
	}

bool FakeString::operator>=(const FakeString &other) const
	{
	return Size >= other.Size;
	}

FakeString &FakeString::operator-=(const FakeString &other)
	{
	return Remove(other);
	}

FakeString &FakeString::operator-=(const char letter)
	{
	return Remove(letter);
	}

FakeString &FakeString::operator+=(const FakeString &other)
	{
	return Append(other);
	}

FakeString &FakeString::operator+=(const char letter)
	{
	return Append(letter);
	}

char &FakeString::operator[](uint32 index)
	{
	FAKE_ASSERT(index <= Size);
	return Data[index];
	}

const char &FakeString::operator[](uint32 index) const
	{
	FAKE_ASSERT(index <= Size);
	return Data[index];
	}

FakeString operator-(FakeString str, const FakeString &other)
	{
	return str.Remove(other);
	}

FakeString operator-(FakeString str, const char letter)
	{
	return str.Remove(letter);
	}

FakeString operator-(FakeString str, const char *other)
	{
	return str.Remove(other);
	}

FakeString operator+(FakeString str, const FakeString &other)
	{
	return str.Append(other);
	}

FakeString operator+(FakeString str, const char letter)
	{
	return str.Append(letter);
	}

FakeString operator+(FakeString str, const char *other)
	{
	return str.Append(other);
	}

std::ostream &operator<<(std::ostream &stream, const FakeString &str)
	{
	for (uint32 i = 0; i < str.Size; ++i)
		stream << str.Data[i];

	return stream;
	}
