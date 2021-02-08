#include "FakePch.h"
#include "Engine/Core/FakeFileSystem.h"

#ifdef FAKE_PLATFORM_WINDOWS
#include <Windows.h>
#include <fileapi.h>

namespace Utils
	{
	void CALLBACK fake_file_io_complete_routine(DWORD errorCode, DWORD numberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
		{
		}

	static HANDLE fake_open_file_internal(const FakeString &path)
		{
		return CreateFileW(path.W_Str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
		}

	static int64 fake_get_file_size_internal(HANDLE file)
		{
		LARGE_INTEGER size;
		GetFileSizeEx(file, &size);
		return size.QuadPart;
		}

	static bool fake_read_file_internal(HANDLE file, void *buffer, int64 size)
		{
		OVERLAPPED ol = { 0 };
		return ReadFileEx(file, buffer, (DWORD) size, &ol, fake_file_io_complete_routine);
		}
	}

bool FakeFileSystem::FileExists(const FakeString &path)
	{
	DWORD result = GetFileAttributesW(path.W_Str());
	return !(result == INVALID_FILE_ATTRIBUTES && GetLastError() == ERROR_FILE_NOT_FOUND);
	}

bool FakeFileSystem::PathExists(const FakeString &path)
	{
	DWORD result = GetFileAttributesW(path.W_Str());
	return (result != INVALID_FILE_ATTRIBUTES && (result & FILE_ATTRIBUTE_DIRECTORY));
	}

bool FakeFileSystem::RemoveFile(const FakeString &path)
	{
	return DeleteFileW(path.W_Str());
	}

bool FakeFileSystem::CreateFolder(const FakeString &path)
	{
	return CreateDirectoryW(path.W_Str(), NULL);
	}

bool FakeFileSystem::RemoveFolder(const FakeString &path)
	{
	return RemoveDirectoryW(path.W_Str());
	}

int64 FakeFileSystem::GetFileSize(const FakeString &path)
	{
	HANDLE file = Utils::fake_open_file_internal(path);
	if (file == INVALID_HANDLE_VALUE)
		return -1;

	int64 size = Utils::fake_get_file_size_internal(file);
	CloseHandle(file);
	return size;
	}

Byte *FakeFileSystem::ReadFile(const FakeString &path, int64 *outSize)
	{
	HANDLE file = Utils::fake_open_file_internal(path);
	int64 size = Utils::fake_get_file_size_internal(file);
	Byte *buffer = new Byte[size];
	bool result = Utils::fake_read_file_internal(file, buffer, size);
	CloseHandle(file);

	if (!result)
		delete[] buffer;

	*outSize = size;
	return result ? buffer : nullptr;
	}

FakeString FakeFileSystem::ReadTextFile(const FakeString &path)
	{
	HANDLE file = Utils::fake_open_file_internal(path);
	int64 size = Utils::fake_get_file_size_internal(file);

	FakeString result;
	result.Resize(size);

	bool success = Utils::fake_read_file_internal(file, &result[0], size);
	CloseHandle(file);
	return success ? result : FakeString("");
	}

bool FakeFileSystem::WriteFile(const FakeString &path, Byte *buffer, int64 size)
	{
	HANDLE file = CreateFileW(path.W_Str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE)
		return false;

	DWORD written;
	bool result = ::WriteFile(file, buffer, (DWORD)size, &written, NULL);
	CloseHandle(file);
	return result;
	}

bool FakeFileSystem::WriteTextFile(const FakeString &path, const FakeString &text)
	{
	return WriteFile(path, (Byte *) &text[0], (int64) text.Length());
	}

void FakeFileSystem::OpenInExplorer(const FakeString &path)
	{
	ShellExecuteW(NULL, L"open", path.W_Str(), NULL, NULL, SW_SHOWDEFAULT);
	}

void FakeFileSystem::OpenInBrowser(const FakeString &url)
	{
	ShellExecuteW(0, 0, url.W_Str(), 0, 0, SW_SHOW);
	}

#endif
