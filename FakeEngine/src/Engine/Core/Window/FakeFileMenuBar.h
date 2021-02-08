/*****************************************************************
 * \file   FakeFileMenuBar.h
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

#include "FakeFileMenu.h"

/**
 *
 * This class represents a Interface for a FileMenuBar that holds all FileMenu entries and renders in some cases the grey background (only if the platform is not windows).
 *
 */
class FAKE_API FakeFileMenuBar : public FakeRefCounted
	{
	public:

		/**
		 *
		 * default destructor.
		 *
		 */
		virtual ~FakeFileMenuBar() = default;

		/**
		 *
		 * Adds a new FileMenu to the Menubar.
		 *
		 * @param menu The menu that should be added.
		 */
		virtual void AddMenu(const FakeRef<FakeFileMenu> &menu) = 0;

		/**
		 *
		 * Removes a FileMenu from the Menubar.
		 *
		 * @param menu The menu that should be removed.
		 */
		virtual void RemoveMenu(const FakeRef<FakeFileMenu> &menu) = 0;

		/**
		 *
		 * Returns the platform specific Menubar handle that contains all FileMenus if any exists.
		 *
		 * @return Returns the platform specific Menubar handle that contains all FileMenus if any exists.
		 */
		virtual void *GetNativeMenuBar() = 0;

		/**
		 *
		 * Returns the platform specific Menubar handle that contains all FileMenus if any exists.
		 *
		 * @return Returns the platform specific Menubar handle that contains all FileMenus if any exists.
		 */
		virtual void *GetNativeMenuBar() const = 0;

		/**
		 *
		 * Creates a new platform specific File Menubar class.
		 *
		 * @return Returns a new platform specific File Menubar class instance.
		 */
		static FakeRef<FakeFileMenuBar> Create();
	};
