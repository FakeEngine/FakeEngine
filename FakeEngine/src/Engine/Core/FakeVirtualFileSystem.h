/*****************************************************************
 * \file   FakeVirtualFileSystem.h
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

#include "Engine/Core/FakeCore.h"
#include "Engine/Core/DataTypes/FakeHashmap.h"

 /**
  *
  * The Virtual FileSystem is a wrapper around the FileSystem of the Engine and should ease up the workflow of the client side programmer.
  *
  * It should shorten the filepaths to actual files on the disk by creating fictional folder names/structures.
  *
  * @warning The VirtualFileSystem is being instantiated and shut down by the Engine because it is also used by the Engine.
  *
  * @attention Please note that the usage of a / as the first character in your filePath indicates that the following part will be a virtual path.
  *
  * ### Usage
  * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
  * // First mount a fictional folder name to a real filepath
  * FakeVirtualFileSystem::Get()->Mount("myFictionalFolderName", "my/path/to/a/real/file.fe");
  *
  * // Then you can access all functions that you could access in the FileSystem with real paths but here you can use your fictional folder structures
  * int64 size;
  * Byte *fileData = FakeVirtualFileSystem::Get()->ReadFile("/myVirtualFolderName/the/real/path/relative/to/the/virtual/folderName", &size);
  * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  */
class FAKE_API FakeVirtualFileSystem
	{
	private:
		static FakeVirtualFileSystem *Instance;
		FakeHashmap<FakeString, std::vector<FakeString>> MountPoints;

	public:

		/**
		 *
		 * Initializes the Virtual File System.
		 * This function is being called automatically by the Engine.
		 *
		 */
		static void Init();

		/**
		 *
		 * Destroys the Virtual File System.
		 * This function is being called automatically by the Engine.
		 *
		 */
		static void Shutdown();

		/**
		 *
		 * Mounts a virtual folderName to a physical folder structure on the disk.
		 * Use this function to register your real paths to a fictional folderName.
		 *
		 * @param virtualPath The fictional folderName that should be replaced by the actual folder structure.
		 * @param physicalPath The actual folderStructure that should replace the fictional folder name when actually accessing files on the disk.
		 */
		void Mount(const FakeString &virtualPath, const FakeString &physicalPath);

		/**
		 *
		 * Deregisters a complete virtual path with all it's real paths attached on.
		 *
		 * @param path The virtual path that should be removed.
		 */
		void Unmount(const FakeString &path);

		/**
		 *
		 * This function translates a virtual folder name to a real path.
		 * This function does not have to be called by the client programmer, it is automatically being called by the other functions of the virtual filesystem.
		 *
		 * @param path The virtula path that should be resolved.
		 * @param outPath The actual physical path that gets set inside this function if the path really exists on the disk.
		 * @return Returns true if the virtual Path has been translated successfully into a physical path.
		 */
		bool ResolvePhysicalPath(FakeString &path, FakeString &outPath);

		/**
		 *
		 * This function takes a virtual path to a file and returns it's content.
		 *
		 * @param path The virtual path to a file on the disk.
		 * @param outSize The Size of a file, that gets set inside this function.
		 * @return Returns the Data read from the File or nullptr on failure.
		 */
		Byte *ReadFile(const FakeString &path, int64 *outSize);

		/**
		 *
		 * This function takes a virtual path to a text file and returns it's content.
		 *
		 * @param path The virtual path to a file on the disk.
		 * @return Returns the Data read from the File or an empty String on failure.
		 */
		FakeString ReadTextFile(const FakeString &path);

		/**
		 *
		 * This function takes a virtual path to a file and stores the provided data in that file.
		 *
		 * @param path The virtual path to a file on the disk.
		 * @param buffer The data which should be stored inside the file.
		 * @param size The Size of the data that should be stored.
		 * @return Returns true if the Data has been written successfully to the disk.
		 */
		bool WriteFile(const FakeString &path, Byte *buffer, int64 size);

		/**
		 *
		 * This function takes a virtual path to a file and stores the provided String in that file.
		 *
		 * @param path The virtual path to a file on the disk.
		 * @param text The Text that should be stored in the file.
		 * @return Returns true if the Data has been written successfully to the disk.
		 */
		bool WriteTextFile(const FakeString &path, const FakeString &text);

		/**
		 *
		 * This function takes a virtual path to a file and removes it from the disk.
		 *
		 * @param path The virtual path to a file on the disk.
		 * @return Returns true if the File has been removed from the disk successfully.
		 */
		bool RemoveFile(const FakeString &path);

		/**
		 *
		 * This function takes a virtual path to a file and returns the size of it.
		 *
		 * @param path The virtual path to a file on the disk.
		 * @return Returns the Size in bytes of the file on the disk.
		 */
		int64 GetFileSize(const FakeString &path);

		/**
		 *
		 * This function takes a virtual path to a file and checks if it exists.
		 *
		 * @param path The virtual path to a file on the disk.
		 * @return Returns true if the File exists on the disk.
		 */
		bool FileExists(const FakeString &path);

		/**
		 *
		 * This function takes a virtual path and checks if it exists.
		 *
		 * @param path The virtual path to a folder on the disk.
		 * @return Returns true if the Path exists on the disk.
		 */
		bool PathExists(const FakeString &path);

		/**
		 *
		 * This function takes a virtual path to a non existing folder and creates it.
		 *
		 * @param path The virtual path to a folder on the disk.
		 * @return Returns true if the folder has been created on the disk.
		 */
		bool CreateFolder(const FakeString &path);

		/**
		 *
		 * This function takes a virtual path to a folder and removes it from the disk.
		 *
		 * @param path The virtual path to a folder on the disk.
		 * @return Returns true if the folder has been removed from the disk.
		 */
		bool RemoveFolder(const FakeString &path);

		/**
		 *
		 * This function takes a virtual path to a file or folder and opens it inside a explorer window.
		 *
		 * @param path The virtual path to a file on the disk.
		 */
		void OpenInExplorer(const FakeString &path);

		/**
		 *
		 * This function takes a URL and opens it in a browser.
		 *
		 * @param url The URL to a server that should be openend.
		 */
		void OpenInBrowser(const FakeString &url);

		/**
		 *
		 * Returns the real physical path calculated by the given virtual path as the parameter.
		 *
		 * @param path The virtual path from which the physical path should be calculated.
		 * @return Returns the physical path of a given virtual path.
		 */
		FakeString GetAbsoluteFilePath(const FakeString &path);

		/**
		 *
		 * Returns a Instance of the virtual Filesystem.
		 *
		 * @return Returns a Instance of the Virtual filesystem.
		 */
		static FakeVirtualFileSystem *Get();
	};
