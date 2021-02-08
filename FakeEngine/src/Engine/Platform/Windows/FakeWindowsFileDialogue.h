/*****************************************************************
 * \file   FakeWindowsFileDialogue.h
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

#include <Windows.h>
#include <ShObjIdl.h>

#include "Engine/Core/Window/FakeFileDialogue.h"

/**
 *
 * This class represents a Windows specific FileDialogue.
 *
 */
class FAKE_API FakeWindowsFileDialogue : public FakeFileDialogue
	{
	private:
		IFileOpenDialog *FileDialogue = nullptr;

		/**
		 *
		 * This method handles the actual implementation of opening the FileDialogue and returning the selected FilePath by the user.
		 *
		 * @param options The mode in which the FileDialogue should be opened
		 * @param open Determines the FileDialogue should show a Save or Open Dialogue.
		 * @return Returns the path which was selected by the user.
		 */
		FakeString OpenFileDialogueInternal(FILEOPENDIALOGOPTIONS options, bool open);

	public:

		/**
		 *
		 * Use this function to select a directory.
		 *
		 * @return Returns the FilePath that was selected by the user.
		 */
		virtual FakeString SelectDirectory() override;

		/**
		 *
		 * Use this function to select a file.
		 *
		 * @return Returns the FilePath that was selected by the user.
		 */
		virtual FakeString SelectFile() override;

		/**
		 *
		 * Use this function to select a save location for any file.
		 *
		 * @return Returns the FilePath that was selected by the user.
		 */
		virtual FakeString SaveFile() override;
	};
