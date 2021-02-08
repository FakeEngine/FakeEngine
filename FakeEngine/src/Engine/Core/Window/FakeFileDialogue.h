/*****************************************************************
 * \file   FakeFileDialogue.h
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

#include "Engine/Core/Window/FakeFileDialogueFilter.h"

 /**
  *
  * This class represents a Interface for a FileDialogue.
  * It can be used to display the OS native window to select a file/folder or to specify a save location for either of these.
  *
  */
class FAKE_API FakeFileDialogue : public FakeRefCounted
	{
	protected:
		FakeFileDialogueFilter Filter;

	public:

		/**
		 *
		 * default destructor.
		 *
		 */
		virtual ~FakeFileDialogue() = default;

		/**
		 *
		 * Sets a new filter. A filter can be used to only allow specific file extensions to display in the selection.
		 *
		 * @param filter The filter that should be applied.
		 */
		void SetFilter(FakeFileDialogueFilter filter);

		/**
		 *
		 * Use this function to select a directory.
		 *
		 * @return Returns the FilePath that was selected by the user.
		 */
		virtual FakeString SelectDirectory() = 0;

		/**
		 *
		 * Use this function to select a file.
		 *
		 * @return Returns the FilePath that was selected by the user.
		 */
		virtual FakeString SelectFile() = 0;

		/**
		 *
		 * Use this function to select a save location for any file.
		 *
		 * @return Returns the FilePath that was selected by the user.
		 */
		virtual FakeString SaveFile() = 0;

		/**
		 *
		 * Creates a new Instance of the platform specific FileDialogue.
		 *
		 * @return Returns a new Instance of the platform specific FileDialogue.
		 */
		static FakeRef<FakeFileDialogue> Create();
	};
