/*****************************************************************
 * \file   FakeFileSystem.h
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
#include "Engine/Core/DataTypes/FakeString.h"

 /**
  *
  * A cross platform implementation of a FileSystem that stores and reads data to the disk.
  *
  */
class FAKE_API FakeFileSystem
	{
	public:

		/**
		 *
		 * This function takes a path to a file and checks if it exists.
		 *
		 * @param path The physical path to a file on the disk.
		 * @return Returns true if the File exists on the disk.
		 */
		static bool FileExists(const FakeString &path);

		/**
		 *
		 * This function takes a path and checks if it exists.
		 *
		 * @param path The physical path to a folder on the disk.
		 * @return Returns true if the Path exists on the disk.
		 */
		static bool PathExists(const FakeString &path);

		/**
		 *
		 * This function takes a path to a file and removes it from the disk.
		 *
		 * @param path The physical path to a file on the disk.
		 * @return Returns true if the File has been removed from the disk.
		 */
		static bool RemoveFile(const FakeString &path);

		/**
		 *
		 * This function takes a path to a file and returns the size of it.
		 *
		 * @param path The physical path to a file on the disk.
		 * @return Returns the Size of the file on the disk.
		 */
		static int64 GetFileSize(const FakeString &path);

		/**
		 *
		 * This function takes a path to a non existing folder and creates it.
		 *
		 * @param path The physical path to a folder on the disk.
		 * @return Returns true if the folder has been created on the disk.
		 */
		static bool CreateFolder(const FakeString &path);

		/**
		 *
		 * This function takes a path to a folder and removes it from the disk.
		 *
		 * @param path The physical path to a folder on the disk.
		 * @return Returns true if the folder has been removed from the disk.
		 */
		static bool RemoveFolder(const FakeString &path);

		/**
		 *
		 * This function takes a path to a file and returns it's content.
		 *
		 * @param path The physical path to a file on the disk.
		 * @param outSize The Size of a file, that gets set inside this function.
		 * @return Returns the Data read from the File or nullptr on failure.
		 */
		static Byte *ReadFile(const FakeString &path, int64 *outSize);

		/**
		 *
		 * This function takes a path to a text file and returns it's content.
		 *
		 * @param path The physical path to a file on the disk.
		 * @return Returns the Data read from the File or an empty String on failure.
		 */
		static FakeString ReadTextFile(const FakeString &path);

		/**
		 *
		 * This function takes a path to a file and stores the provided data in that file.
		 *
		 * @param path The physical path to a file on the disk.
		 * @param buffer The data which should be stored inside the file.
		 * @param size The Size of the data that should be stored.
		 * @return Returns true if the Data has been written successfully to the disk.
		 */
		static bool WriteFile(const FakeString &path, Byte *buffer, int64 size);

		/**
		 *
		 * This function takes a path to a file and stores the provided String in that file.
		 *
		 * @param path The physical path to a file on the disk.
		 * @param text The Text that should be stored in the file.
		 * @return Returns true if the Data has been written successfully to the disk.
		 */
		static bool WriteTextFile(const FakeString &path, const FakeString &text);

		/**
		 *
		 * This function takes a path to a file or folder and opens it inside a explorer window.
		 *
		 * @param path The physical path to a file on the disk.
		 */
		static void OpenInExplorer(const FakeString &path);

		/**
		 *
		 * This function takes a URL and opens it in a browser.
		 *
		 * @param url The URL to a server that should be openend.
		 */
		static void OpenInBrowser(const FakeString &url);
	};
