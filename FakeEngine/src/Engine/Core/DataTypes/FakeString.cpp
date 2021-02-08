#include "FakePch.h"
#include "FakeString.h"

#include "Engine/Utils/FakeStringHelperUtils.h"

void FakeString::CreateHash()
	{
	FAKE_ASSERT(Data != NULL, "String was empty!");
	unsigned long result = 0x3B6C;
	char *ptr = Data;

	int c;
	while (c = *ptr++)
		result = ((result << 5) + result) + c;

	Hash = result;
	}

FakeString::FakeString(const char *str)
	{
	Size = (uint32) strlen(str);
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, str, Size);

	CreateHash();
	}

FakeString::FakeString(const wchar_t *str)
	{
	Size = uint32(wcslen(str));
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, str, Size);

	CreateHash();
	}

FakeString::FakeString(const FakeString &other)
	{
	Size = other.Size;
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, other.Data, Size);

	CreateHash();
	}

FakeString::FakeString(const FakeString &other, uint32 length)
	{
	Size = length;
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, other.Data, Size);

	CreateHash();
	}

FakeString::FakeString(const std::string &str)
	{
	Size = (uint32)strlen(str.c_str());
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, str.c_str(), Size);

	CreateHash();
	}

FakeString::FakeString(const FakeString &other, uint32 start, uint32 end)
	{
	Size = end - start;
	Data = new char[Size + 1];
	Data[Size] = '\0';
	memcpy(Data, &other.Data[start], Size);

	CreateHash();
	}

FakeString::FakeString(FakeString &&other) noexcept
	{
	Size = other.Size;
	Data = other.Data;

	other.Size = 0;
	other.Data = nullptr;

	CreateHash();
	}

FakeString::~FakeString()
	{
	if (Data)
		delete[] Data;
	}

FakeString &FakeString::operator=(const FakeString &other)
	{
	if (this != &other)
		{
		if (Data) delete[] Data;

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
		if (Data) delete[] Data;

		Size = other.Size;
		Data = new char[Size + 1];
		Data[Size] = '\0';

		memcpy(Data, other.Data, Size);
		}

	return *this;
	}

void FakeString::Resize(int64 size)
	{
	if (Data)
		delete[] Data;

	Data = new char[size];
	Size = (uint32)size;
	}

wchar_t *FakeString::W_Str()
	{
	wchar_t *ret = new wchar_t[Size + 1];
	
	for (uint32 i = 0; i < Size; ++i)
		ret[i] = Data[i];

	ret[Size] = '\0';
	return ret;
	}

const wchar_t *FakeString::W_Str() const
	{
	wchar_t *ret = new wchar_t[Size + 1];

	for (uint32 i = 0; i < Size; ++i)
		ret[i] = Data[i];

	ret[Size] = '\0';
	return ret;
	}

char *FakeString::C_Str()
	{
	return Data;
	}

const char *FakeString::C_Str() const
	{
	return Data;
	}

uint32 FakeString::Length() const
	{
	return Size;
	}

unsigned long FakeString::GetHash() const
	{
	return Hash;
	}

char FakeString::At(uint32 i)
	{
	FAKE_ASSERT(i < Size, "");
	return Data[i];
	}

const char FakeString::At(uint32 i) const
	{
	FAKE_ASSERT(i < Size, "");
	return Data[i];
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

	CreateHash();
	return *this;
	}

FakeString &FakeString::Append(const FakeString &other)
	{
	uint32 new_size = Size + other.Size;
	char *new_data = new char[new_size + 1]; // +1 for the null terminator

	new_data[new_size] = '\0';
	if (Data) memcpy(new_data, Data, Size);						// copy existing string data
	memcpy((char *) (new_data + Size), other.Data, other.Size);	// copy appended string data

	if (Data)
		delete[] Data;

	Data = new_data;
	Size = new_size;

	CreateHash();
	return *this;
	}

FakeString &FakeString::Remove(const char letter)
	{
	if (Contains(letter))
		{
		uint32 i = 0;
		uint32 j = 0;
		uint32 start_pos = Find(letter);
		uint32 new_size = Size - 1;
		char *new_data = new char[new_size];

		if (Data)
			{
			// Copy the part before the letter, if there is a part
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
			}

		Data = new_data;
		Size = new_size;
		}

	CreateHash();
	return *this;
	}

FakeString &FakeString::Remove(const FakeString &other)
	{
	if (Contains(other))
		{
		uint32 i = 0;
		uint32 j = 0;
		uint32 start_pos = Find(other);
		uint32 new_size = Size - other.Length();
		char *new_data = new char[new_size];

		if (Data)
			{
			if (start_pos > 0)
				memcpy(new_data, Data, start_pos); // Copy only the part before other if there is a part before it

			// Copy the part after other
			for (i = start_pos + other.Length(); i < Size; ++i)
				{
				new_data[j] = Data[i];
				++j;
				}

			delete[] Data;
			}

		Data = new_data;
		Size = new_size;
		}

	CreateHash();
	return *this;
	}

uint32 FakeString::FirstIndexOf(const char letter)
	{
	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == letter)
			return i;
		}

	return NPOS;
	}

uint32 FakeString::FirstIndexOf(const char letter) const
	{
	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == letter)
			return i;
		}

	return NPOS;
	}

uint32 FakeString::FirstIndexOf(const FakeString &other, uint32 offset)
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

uint32 FakeString::IndexOf(const char letter, uint32 offset)
	{
	if (0 == offset)
		return FirstIndexOf(letter);

	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == letter && offset > 0)
			{
			--offset;
			continue;
			}

		if (Data[i] == letter)
			return i;
		}

	return NPOS;
	}

uint32 FakeString::IndexOf(const char letter, uint32 offset) const
	{
	if (0 == offset)
		return FirstIndexOf(letter);

	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == letter && offset > 0)
			{
			--offset;
			continue;
			}

		if (Data[i] == letter)
			return i;
		}

	return NPOS;
	}

uint32 FakeString::IndexOf(const FakeString &other, uint32 offset)
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

uint32 FakeString::LastIndexOf(const char letter)
	{
	// Count how many times the letter exists
	uint32 letterCount = 0;
	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == letter)
			letterCount++;
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
			{
			return i;
			}
		}

	return NPOS;
	}

uint32 FakeString::LastIndexOf(const char letter) const
	{
	// Count how many times the letter exists
	uint32 letterCount = 0;
	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == letter)
			letterCount++;
		}

	// If No Letter exists, return
	if (0 == letterCount)
		return NPOS;

	// Get the last letter index
	for (uint32 i = 0; i < Size; ++i)
		{
		if (Data[i] == letter && letterCount > 1)
			{
			--letterCount;
			continue;
			}

		if (Data[i] == letter)
			{
			return i;
			}
		}

	return NPOS;
	}

uint32 FakeString::LastIndexOf(const FakeString &other)
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

uint32 FakeString::LastIndexOf(const FakeString &other) const
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

uint32 FakeString::FirstIndexNotOf(const FakeString &other, uint32 offset)
	{
	const int len = static_cast<int>(strspn(Data + offset, *other));
	if (len + offset == Size)
		return NPOS;
	else
		return len + offset;
	}

uint32 FakeString::FirstIndexNotOf(const FakeString &other, uint32 offset) const
	{
	const int len = static_cast<int>(strspn(Data + offset, *other));
	if (len + offset == Size)
		return NPOS;
	else
		return len + offset;
	}

std::vector<FakeString> FakeString::Split(char delimiter)
	{
	// First get the word count to construct the size of the array
	// Then iterate through the string and put every word into the array
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
			{
			++charIdx;
			}

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
			{
			++charIdx;
			}

		word = Substr(wordBeginIdx, charIdx);
		result[i] = word;
		++charIdx;
		}

	if (outWordCount)
		*outWordCount = wordCount;

	return result;
	}

FakeString FakeString::Substr(uint32 beginIndex, uint32 endIndex)
	{
	if (endIndex == 0)
		endIndex = Size;

	if ((endIndex - beginIndex) > Size)
		return FakeString("-1");

	return FakeString(*this, beginIndex, endIndex);
	}

FakeString FakeString::Substr(uint32 beginIndex, uint32 endIndex) const
	{
	if (endIndex == 0)
		endIndex = Size;

	if ((endIndex - beginIndex) > Size)
		return FakeString("-1");

	return FakeString(*this, beginIndex, endIndex);
	}

bool FakeString::Contains(const char letter, uint32 offset)
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

bool FakeString::Contains(const FakeString &other, uint32 offset)
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

uint32 FakeString::Find(const char letter, uint32 offset) const noexcept
	{
	uint32 i = 0;
	uint32 pos = 0;

	for (i = offset; i < Size; ++i)
		{
		if (Data[i] == letter)
			{
			pos = i;
			break;
			}
		}

	return NPOS;
	}

uint32 FakeString::Find(const FakeString &other, uint32 offset) const noexcept
	{
	uint32 i = 0;
	uint32 j = 0;

	for (i = offset; i < Size; ++i)
		{
		if (Data[i] == other.Data[0])
			{
			bool valid = true;
			for (j = 0; j < other.Size; ++j)
				{
				if (Data[i + j] == '\0' || Data[i + j] != other.Data[j])
					{
					valid = false;
					break;
					}
				}

			if (valid)
				return i;

			i += other.Size - 1;
			}
		}

	return NPOS;
	}

FakeString &FakeString::Replace(const FakeString &find, const FakeString &replaceValue, uint32 occurencesToReplace)
	{
	uint32 occurences = 0;
	uint32 offset = 0;

	while (Contains(find, offset))
		{
		occurences++;
		offset = Find(find, offset) + find.Length();

		if (occurencesToReplace && occurences == occurencesToReplace)
			break;
		}

	if (!occurences)
		return *this;

	uint32 *occurence_indices = new uint32[occurences];
	offset = 0;
	for (uint32 i = 0; i < occurences; ++i)
		{
		occurence_indices[i] = Find(find, offset);
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

	CreateHash();
	return *this;
	}

FakeString &FakeString::ToLowerCase()
	{
	for (uint32 i = 0; i < Size; ++i)
		Data[i] = fake_string_helper_to_lower_case(Data[i]);

	CreateHash();
	return *this;
	}

const FakeString &FakeString::ToLowerCase() const
	{
	for (uint32 i = 0; i < Size; ++i)
		Data[i] = fake_string_helper_to_lower_case(Data[i]);

	return *this;
	}

FakeString &FakeString::ToUpperCase()
	{
	for (uint32 i = 0; i < Size; ++i)
		Data[i] = fake_string_helper_to_upper_case(Data[i]);

	CreateHash();
	return *this;
	}

const FakeString &FakeString::ToUpperCase() const
	{
	for (uint32 i = 0; i < Size; ++i)
		Data[i] = fake_string_helper_to_upper_case(Data[i]);

	return *this;
	}

FakeString &FakeString::Reverse()
	{
	for (uint32 i = 0; i < Size / 2; i++)
		{
		char temp = Data[i];
		Data[i] = Data[Size - i - 1];
		Data[Size - i - 1] = temp;
		}

	CreateHash();
	return *this;
	}

void FakeString::Print()
	{
	for (uint32 i = 0; i < Size; i++)
		printf("%c", Data[i]);

	printf("\n");
	}

void FakeString::Print() const
	{
	for (uint32 i = 0; i < Size; i++)
		printf("%c", Data[i]);

	printf("\n");
	}

bool FakeString::IsEmpty()
	{
	return Size == 0;
	}

bool FakeString::IsEmpty() const
	{
	return Size == 0;
	}

bool FakeString::StartsWith(const char letter)
	{
	if (Data[0] == letter)
		return true;
	else
		return false;
	}

bool FakeString::StartsWith(const char letter) const
	{
	if (Data[0] == letter)
		return true;
	else
		return false;
	}

bool FakeString::StartsWith(const FakeString &other)
	{
	uint32 equalCounter = 0;
	for (uint32 i = 0; i < other.Size; ++i)
		{
		if (Data[i] == other[i])
			++equalCounter;
		}

	if (other.Size == equalCounter)
		return true;
	else
		return false;
	}

bool FakeString::StartsWith(const FakeString &other) const
	{
	uint32 equalCounter = 0;
	for (uint32 i = 0; i < other.Size; ++i)
		{
		if (Data[i] == other[i])
			++equalCounter;
		}

	if (other.Size == equalCounter)
		return true;
	else
		return false;
	}

bool FakeString::EndsWith(const char letter)
	{
	if (Data[Size - 1] == letter)
		return true;
	else
		return false;
	}

bool FakeString::EndsWith(const char letter) const
	{
	if (Data[Size - 1] == letter)
		return true;
	else
		return false;
	}

bool FakeString::EndsWith(const FakeString &other)
	{
	uint32 equalCounter = 0;
	uint32 startPos = Size - other.Size;
	uint32 i = 0;
	uint32 j = 0;

	for (i = startPos; i < Size; ++i)
		{
		for (j = 0; j < other.Size; ++j)
			{
			if (Data[i] == other[j])
				++equalCounter;
			}
		}

	if (equalCounter == other.Size)
		return true;
	else
		return false;
	}

bool FakeString::EndsWith(const FakeString &other) const
	{
	uint32 equalCounter = 0;
	uint32 startPos = Size - other.Size;
	uint32 i = 0;
	uint32 j = 0;

	for (i = startPos; i < Size; ++i)
		{
		for (j = 0; j < other.Size; ++j)
			{
			if (Data[i] == other[j])
				++equalCounter;
			}
		}

	if (equalCounter == other.Size)
		return true;
	else
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
	char *result = new char[Size + 1];
	for (uint32 i = 0; i < Size; ++i)
		result[i] = Data[i];

	result[Size + 1] = '\0';
	return result;
	}

FakeString::operator const char *() const
	{
	char *result = new char[Size + 1];
	for (uint32 i = 0; i < Size; ++i)
		result[i] = Data[i];

	result[Size + 1] = '\0';
	return result;
	}

bool FakeString::operator==(const char *other)
	{
	uint32 charEqualCount = 0;
	uint32 i = 0;

	for (i = 0; i < Size; ++i)
		{
		if (Data[i] == other[i])
			++charEqualCount;
		}

	if (Size == strlen(other) && charEqualCount == Size)
		return true;

	return false;
	}

bool FakeString::operator==(const char *other) const
	{
	uint32 charEqualCount = 0;
	uint32 i = 0;

	for (i = 0; i < Size; ++i)
		{
		if (Data[i] == other[i])
			++charEqualCount;
		}

	if (Size == strlen(other) && charEqualCount == Size)
		return true;

	return false;
	}

bool FakeString::operator==(const FakeString &other)
	{
	uint32 charEqualCount = 0;
	uint32 i = 0;

	for (i = 0; i < Size; ++i)
		{
		if (Data[i] == other[i])
			++charEqualCount;
		}

	if (Size == other.Size && charEqualCount == Size)
		return true;

	return false;
	}

bool FakeString::operator==(const FakeString &other) const
	{
	uint32 charEqualCount = 0;
	uint32 i = 0;

	for (i = 0; i < Size; ++i)
		{
		if (Data[i] == other[i])
			++charEqualCount;
		}

	if (Size == other.Size && charEqualCount == Size)
		return true;

	return false;
	}

bool FakeString::operator!=(const char *other)
	{
	uint32 charNotEqualCount = 0;
	uint32 i = 0;

	for (i = 0; i < Size; ++i)
		{
		if (Data[i] != other[i])
			++charNotEqualCount;
		}

	if (Size != strlen(other) || charNotEqualCount == Size)
		return true;

	return false;
	}

bool FakeString::operator!=(const char *other) const
	{
	uint32 charNotEqualCount = 0;
	uint32 i = 0;

	for (i = 0; i < Size; ++i)
		{
		if (Data[i] != other[i])
			++charNotEqualCount;
		}

	if (Size != strlen(other) || charNotEqualCount == Size)
		return true;

	return false;
	}

bool FakeString::operator!=(const FakeString &other)
	{
	return !(*this == other);
	}

bool FakeString::operator!=(const FakeString &other) const
	{
	return !(*this == other);
	}

bool FakeString::operator<(const char *other)
	{
	return Size < strlen(other);
	}

bool FakeString::operator<(const char *other) const
	{
	return Size < strlen(other);
	}

bool FakeString::operator<(const FakeString &other)
	{
	return Size < other.Size;
	}

bool FakeString::operator<(const FakeString &other) const
	{
	return Size < other.Size;
	}

bool FakeString::operator>(const char *other)
	{
	return Size > strlen(other);
	}

bool FakeString::operator>(const char *other) const
	{
	return Size > strlen(other);
	}


bool FakeString::operator>(const FakeString &other)
	{
	return Size > other.Size;
	}

bool FakeString::operator>(const FakeString &other) const
	{
	return Size > other.Size;
	}

bool FakeString::operator<=(const char *other)
	{
	return Size <= strlen(other);
	}

bool FakeString::operator<=(const char *other) const
	{
	return Size <= strlen(other);
	}

bool FakeString::operator<=(const FakeString &other)
	{
	return Size <= other.Size;
	}

bool FakeString::operator<=(const FakeString &other) const
	{
	return Size <= other.Size;
	}

bool FakeString::operator>=(const char *other)
	{
	return Size >= strlen(other);
	}

bool FakeString::operator>=(const char *other) const
	{
	return Size >= strlen(other);
	}

bool FakeString::operator>=(const FakeString &other)
	{
	return Size >= other.Size;
	}

bool FakeString::operator>=(const FakeString &other) const
	{
	return Size >= other.Size;
	}

FakeString &FakeString::operator-=(const char letter)
	{
	return Remove(letter);
	}

FakeString &FakeString::operator-=(const FakeString &other)
	{
	return Remove(other);
	}

FakeString &FakeString::operator+=(const char letter)
	{
	return Append(letter);
	}

FakeString &FakeString::operator+=(const FakeString &other)
	{
	return Append(other);
	}

char &FakeString::operator[](uint32 i)
	{
	FAKE_ASSERT(i <= Size); // <= because of null terminator
	return Data[i];
	}

const char &FakeString::operator[](uint32 i) const
	{
	FAKE_ASSERT(i <= Size); // <= because of null terminator
	return Data[i];
	}

FakeString operator-(FakeString str, const char letter)
	{
	return str.Remove(letter);
	}

FakeString operator-(FakeString str, const FakeString &other)
	{
	return str.Remove(other);
	}

FakeString operator+(FakeString str, const char letter)
	{
	return str.Append(letter);
	}

FakeString operator+(FakeString str, const FakeString &other)
	{
	return str.Append(other);
	}

std::ostream &operator<<(std::ostream &stream, const FakeString &string)
	{
	for (uint32 i = 0; i < string.Size; ++i)
		stream << string[i];

	return stream;
	}

