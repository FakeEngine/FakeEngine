#include "FakePch.h"
#include "FakeVirtualFileSystem.h"

#include "Engine/Core/FakeFileSystem.h"

FakeVirtualFileSystem *FakeVirtualFileSystem::Instance = nullptr;

void FakeVirtualFileSystem::Init()
	{
	Instance = new FakeVirtualFileSystem();
	}

void FakeVirtualFileSystem::Shutdown()
	{
	delete Instance;
	}

void FakeVirtualFileSystem::Mount(const FakeString &virtualPath, const FakeString &physicalPath)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");

	if (MountPoints.HasKey(virtualPath))
		{
		MountPoints[virtualPath].push_back(physicalPath);
		}
	else
		{
		std::vector<FakeString> res;
		res.push_back(physicalPath);
		MountPoints.Put(virtualPath, res);
		}
	}

void FakeVirtualFileSystem::Unmount(const FakeString &path)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");
	MountPoints[path].clear();
	}

bool FakeVirtualFileSystem::ResolvePhysicalPath(FakeString &path, FakeString &outPath)
	{
	if (path.IsEmpty())
		return false;

	if (path[0] != '/')
		{
		outPath = path;
		return FakeFileSystem::FileExists(path);
		}

	path = path.Substr(1);
	std::vector<FakeString> dirs = path.Split('/');
	const FakeString &virtualDir = dirs.front();
	const FakeString &fileName = dirs.back();

	if (!MountPoints.HasKey(virtualDir) || MountPoints.IsEmpty())
		return false;

	for (const FakeString &physicalPath : MountPoints[virtualDir])
		{
		FakeString p = physicalPath + fileName;
		if (FakeFileSystem::FileExists(p) || FakeFileSystem::PathExists(physicalPath))
			{
			outPath = p;
			return true;
			}
		}

	return false;
	}

Byte *FakeVirtualFileSystem::ReadFile(const FakeString &path, int64 *outSize)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");
	FakeString physicalPath;
	return ResolvePhysicalPath(FakeString(path), physicalPath) ? FakeFileSystem::ReadFile(physicalPath, outSize) : nullptr;
	}

FakeString FakeVirtualFileSystem::ReadTextFile(const FakeString &path)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");
	FakeString physicalPath;
	return ResolvePhysicalPath(FakeString(path), physicalPath) ? FakeFileSystem::ReadTextFile(physicalPath) : FakeString();
	}

bool FakeVirtualFileSystem::WriteFile(const FakeString &path, Byte *buffer, int64 size)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");
	FakeString physicalPath;
	return ResolvePhysicalPath(FakeString(path), physicalPath) ? FakeFileSystem::WriteFile(physicalPath, buffer, size) : false;
	}

bool FakeVirtualFileSystem::WriteTextFile(const FakeString &path, const FakeString &text)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");
	FakeString physicalPath;
	return ResolvePhysicalPath(FakeString(path), physicalPath) ? FakeFileSystem::WriteTextFile(physicalPath, text) : false;
	}

bool FakeVirtualFileSystem::RemoveFile(const FakeString &path)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");
	FakeString physicalPath;
	return ResolvePhysicalPath(FakeString(path), physicalPath) ? FakeFileSystem::RemoveFile(physicalPath) : false;
	}

int64 FakeVirtualFileSystem::GetFileSize(const FakeString &path)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");
	FakeString physicalPath;
	return ResolvePhysicalPath(FakeString(path), physicalPath) ? FakeFileSystem::GetFileSize(physicalPath) : -1;
	}

bool FakeVirtualFileSystem::FileExists(const FakeString &path)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");
	FakeString physicalPath;
	return ResolvePhysicalPath(FakeString(path), physicalPath) ? FakeFileSystem::FileExists(physicalPath) : false;
	}

bool FakeVirtualFileSystem::PathExists(const FakeString &path)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");
	FakeString physicalPath;
	return ResolvePhysicalPath(FakeString(path), physicalPath) ? FakeFileSystem::PathExists(physicalPath) : false;
	}

bool FakeVirtualFileSystem::CreateFolder(const FakeString &path)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");
	FakeString physicalPath;
	return ResolvePhysicalPath(FakeString(path), physicalPath) ? FakeFileSystem::CreateFolder(physicalPath) : false;
	}

bool FakeVirtualFileSystem::RemoveFolder(const FakeString &path)
	{
	FAKE_ASSERT(Instance, "FileSystem not created!");
	FakeString physicalPath;
	return ResolvePhysicalPath(FakeString(path), physicalPath) ? FakeFileSystem::RemoveFolder(physicalPath) : false;
	}

void FakeVirtualFileSystem::OpenInExplorer(const FakeString &path)
	{
	FakeFileSystem::OpenInExplorer(path);
	}

void FakeVirtualFileSystem::OpenInBrowser(const FakeString &url)
	{
	FakeFileSystem::OpenInBrowser(url);
	}

FakeString FakeVirtualFileSystem::GetAbsoluteFilePath(const FakeString &path)
	{
	FakeString physicalPath;
	FakeString p = path;
	ResolvePhysicalPath(p, physicalPath);
	return physicalPath;
	}

FakeVirtualFileSystem *FakeVirtualFileSystem::Get()
	{
	return Instance;
	}
