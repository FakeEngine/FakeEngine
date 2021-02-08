/*****************************************************************
 * \file   FakeWindowsPopupMenu.h
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

#include "Engine/Core/Window/FakePopupMenu.h"

 /**
  *
  * This class represents a windows specific Popup menu.
  * Popup Menus can be accessed by right clicking onto the window.
  *
  */
class FAKE_API FakeWindowsPopupMenu : public FakePopupMenu
	{
	private:
		HMENU PopupMenu;
		int32 LastPosition = 0;
		FakeString Name;

	public:

		/**
		 *
		 * constructor that initializes the PopupMenu instance.
		 *
		 * @param name The Name of the windows specific Popup Menu.
		 */
		FakeWindowsPopupMenu(const FakeString &name);

		/**
		 *
		 * virtual destructor.
		 *
		 */
		virtual ~FakeWindowsPopupMenu();

		/**
		 *
		 * Adds a new PopupMenu Entry to the Menu.
		 *
		 * @param item The Item that should be added.
		 */
		virtual void AddMenuItem(const FakeRef<FakePopupMenuItem> &item) override;

		/**
		 *
		 * Adds a new PopupMenu Entry to the Menu.
		 *
		 * @param name The name of the PopupMenu Entry that should be displayed.
		 * @param id The ID of the PopupMenu Entry that should be used.
		 * @param position The Position of the PopupMenu Entry in the Menu.
		 * @param visible Determines whether the PopupMenu is clickable or not.
		 */
		virtual void AddMenuItem(const FakeString &name, int32 id, int32 position, bool visible = true) override;

		/**
		 *
		 * Adds a new Seperator to the Menu.
		 *
		 */
		virtual void AddSeperator() override;

		/**
		 *
		 * Adds another Menu as a Submenu to the Menu instance.
		 *
		 * @param other The SubMenu that should be added to the Menu.
		 */
		virtual void AddSubMenu(const FakeRef<FakePopupMenu> &other) override;

		/**
		 *
		 * This function displays the Rightclick Menu if the right mouse button is pressed.
		 *
		 */
		virtual void Show() override;

		/**
		 *
		 * Returns the windows specific PopupMenu handle that contains the PopupMenu if any exists.
		 *
		 * @return Returns the windows specific PopupMenu handle that contains the PopupMenu if any exists.
		 */
		virtual void *GetPopupMenuHandle() override;

		/**
		 *
		 * Returns the windows specific PopupMenu handle that contains the PopupMenu if any exists.
		 *
		 * @return Returns the windows specific PopupMenu handle that contains the PopupMenu if any exists.
		 */
		virtual void *GetPopupMenuHandle() const override;

		/**
		 *
		 * Returns the Root name of the PopupMenu.
		 *
		 * @return Returns the Root name of the PopupMenu.
		 */
		virtual FakeString &GetName() override;

		/**
		 *
		 * Returns the Root name of the PopupMenu.
		 *
		 * @return Returns the Root name of the PopupMenu.
		 */
		virtual const FakeString &GetName() const override;
	};
