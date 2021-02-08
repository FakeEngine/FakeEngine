/*****************************************************************
 * \file   FakeFileDialogueFilter.h
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

 /**
  *
  * This class represents the Filter that is used for the FileDialogue.
  * Filters can be used to select specifc file types which should be selectable in the FileDialogue.
  *
  */
class FAKE_API FakeFileDialogueFilter
	{
	private:
		std::map<FakeString, FakeString> Filters;

	public:

		/**
		 *
		 * Adds a new filter that should be used for the FileDialogue.
		 *
		 * @param name The name that should be displayed as the Filetype.
		 * @param format The actual filter that should be used internally.
		 */
		void AddFilter(const FakeString &name, const FakeString &format);

		/**
		 *
		 * Returns if any filter were already added or not.
		 *
		 * @return Returns true if any filters were added.
		 */
		bool HasFilters();

		/**
		 *
		 * Returns all filters that were set.
		 *
		 * @return Returns a map of filters.
		 */
		std::map<FakeString, FakeString> &GetFilters();
	};

