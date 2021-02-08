/*****************************************************************
 * \file   FakeFileMenu.h
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

/**
 *
 * This class represents a FileMenuItem that contains the Data needed for a file menu entry.
 *
 */
struct FAKE_API FakeFileMenuItem : public FakeRefCounted
	{
	FakeString Name = "Default MenuItem";
	int32 ID = 0;
	bool Visible = true;
	bool Seperator = false;

	FakeFileMenuItem() = default;

	FakeFileMenuItem(const FakeString &name, int32 id, bool visible = true, bool seperator = false)
		: Name(name), ID(id), Visible(visible), Seperator(seperator)
		{
		}

	FakeFileMenuItem(const FakeFileMenuItem &other)
		: Name(other.Name), ID(other.ID), Visible(other.Visible), Seperator(other.Seperator)
		{
		}
	};

/**
 *
 * This class represents a Interface for a FileMenu that holds the FileMenuItems.
 *
 */
class FAKE_API FakeFileMenu : public FakeRefCounted
	{
	public:

		/**
		 *
		 * default constructor.
		 *
		 */
		FakeFileMenu() = default;

		/**
		 *
		 * default destructor.
		 *
		 */
		virtual ~FakeFileMenu() = default;

		/**
		 *
		 * Adds a new Item to the FileMenu.
		 *
		 * @param item The Item that should be added.
		 */
		virtual void AddMenuItem(const FakeRef<FakeFileMenuItem> &item) = 0;

		/**
		 *
		 * Adds a new Item to the FileMenu.
		 *
		 * @param item The Item that should be added.
		 */
		virtual void AddMenuItem(const FakeFileMenuItem &item) = 0;

		/**
		 *
		 * Adds a new Item to the FileMenu.
		 *
		 * @param name The name of the Menu Entry.
		 * @param id The ID of the Menu Entry.
		 * @param visible Determines if the FileMenu Entry is selectable or not.
		 */
		virtual void AddMenuItem(const FakeString &name, int32 id, bool visible = true) = 0;

		/**
		 *
		 * Adds a new SubMenu to the Menu.
		 *
		 * @param other The SubMenu that should be added to the menu.
		 */
		virtual void AddSubMenu(const FakeRef<FakeFileMenu> &other) = 0;

		/**
		 *
		 * Adds a new Seperator (grey line) to the Menu to seperate specific menu entries.
		 *
		 */
		virtual void AddMenuSeperator() = 0;

		/**
		 *
		 * Returns the platform specific Menu handle that contains the FileMenu if any exists.
		 *
		 * @return Returns the platform specific Menu handle that contains the FileMenu if any exists.
		 */
		virtual void *GetMenuHandle() = 0;

		/**
		 *
		 * Returns the platform specific Menu handle that contains the FileMenu if any exists.
		 *
		 * @return Returns the platform specific Menu handle that contains the FileMenu if any exists.
		 */
		virtual void *GetMenuHandle() const = 0;

		/**
		 *
		 * Returns the Root name of the FileMenu.
		 *
		 * @return Returns the Root name of the FileMenu.
		 */
		virtual FakeString &GetName() = 0;

		/**
		 *
		 * Returns the Root name of the FileMenu.
		 *
		 * @return Returns the Root name of the FileMenu.
		 */
		virtual const FakeString &GetName() const = 0;

		/**
		 *
		 * Enables or disables a particular menu Item in a menu.
		 *
		 * @param id The ID of the MenuItem, that should be enabled or disabled.
		 * @param enabled Indicates whether the MenuItem should be enabled or disabled.
		 * @return Returns true, if the MenuItem was modified successfully.
		 */
		virtual bool EnableMenuItem(int32 id, bool enabled) = 0;

		/**
		 *
		 * Creates a new platform specific FileMenu class.
		 *
		 * @param name The name that should be displayed as the root name for the fileMenu (something like File or Help)
		 * @return Returns a new platform specific FileMenu class instance.
		 */
		static FakeRef<FakeFileMenu> Create(const FakeString &name);
	};

