/*****************************************************************
 * \file   FakeWindowsFileMenu.h
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

#include "Engine/Core/FakeCore.h"
#include "Engine/Core/Window/FakeFileMenu.h"

/**
 *
 * This class represents a Windows specific FileMenu that holds the FileMenuItems.
 *
 */
class FAKE_API FakeWindowsFileMenu : public FakeFileMenu
	{
	private:
		FakeString Name;
		HMENU Menu;

	public:

		/**
		 *
		 * constructor that initializes a Windows FileMenu Entry.
		 *
		 * @param name The Root name of the Windows FileMenu.
		 */
		FakeWindowsFileMenu(const FakeString &name);

		/**
		 *
		 * virtual destructor.
		 *
		 */
		virtual ~FakeWindowsFileMenu();

		/**
		 *
		 * Adds a new Item to the FileMenu.
		 *
		 * @param item The Item that should be added.
		 */
		virtual void AddMenuItem(const FakeRef<FakeFileMenuItem> &item) override;

		/**
		 *
		 * Adds a new Item to the FileMenu.
		 *
		 * @param item The Item that should be added.
		 */
		virtual void AddMenuItem(const FakeFileMenuItem &item) override;

		/**
		 *
		 * Adds a new Item to the FileMenu.
		 *
		 * @param name The name of the Menu Entry.
		 * @param id The ID of the Menu Entry.
		 * @param visible Determines if the FileMenu Entry is selectable or not.
		 */
		virtual void AddMenuItem(const FakeString &name, int32 id, bool visible = true) override;

		/**
		 *
		 * Adds a new SubMenu to the Menu.
		 *
		 * @param other The SubMenu that should be added to the menu.
		 */
		virtual void AddSubMenu(const FakeRef<FakeFileMenu> &other) override;

		/**
		 *
		 * Adds a new Seperator (grey line) to the Menu to seperate specific menu entries.
		 *
		 */
		virtual void AddMenuSeperator() override;

		/**
		 *
		 * Returns the windows specific Menu handle that contains the FileMenu if any exists.
		 *
		 * @return Returns the windows specific Menu handle that contains the FileMenu if any exists.
		 */
		virtual void *GetMenuHandle() override;

		/**
		 *
		 * Returns the windows specific Menu handle that contains the FileMenu if any exists.
		 *
		 * @return Returns the windows specific Menu handle that contains the FileMenu if any exists.
		 */
		virtual void *GetMenuHandle() const override;

		/**
		 *
		 * Returns the Root name of the FileMenu.
		 *
		 * @return Returns the Root name of the FileMenu.
		 */
		virtual FakeString &GetName() override;

		/**
		 *
		 * Returns the Root name of the FileMenu.
		 *
		 * @return Returns the Root name of the FileMenu.
		 */
		virtual const FakeString &GetName() const override;

		/**
		 *
		 * Enables or disables a particular menu Item in a menu.
		 *
		 * @param id The ID of the MenuItem, that should be enabled or disabled.
		 * @param enabled Indicates whether the MenuItem should be enabled or disabled.
		 * @return Returns true, if the MenuItem was modified successfully.
		 */
		virtual bool EnableMenuItem(int32 id, bool enabled) override;
	};
