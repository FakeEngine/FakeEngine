/*****************************************************************
 * \file   FakePopupMenu.h
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

#include "Engine/Core/Window/FakePopupMenuItem.h"

 /**
  *
  * This class represents a Interface for Popup menus.
  * Popup Menus can be accessed by right clicking onto the window.
  *
  */
class FAKE_API FakePopupMenu : public FakeRefCounted
	{
	public:

		/**
		 *
		 * default destructor.
		 *
		 */
		virtual ~FakePopupMenu() = default;

		/**
		 *
		 * Adds a new PopupMenu Entry to the Menu.
		 *
		 * @param item The Item that should be added.
		 */
		virtual void AddMenuItem(const FakeRef<FakePopupMenuItem> &item) = 0;

		/**
		 *
		 * Adds a new PopupMenu Entry to the Menu.
		 *
		 * @param name The name of the PopupMenu Entry that should be displayed.
		 * @param id The ID of the PopupMenu Entry that should be used.
		 * @param position The Position of the PopupMenu Entry in the Menu.
		 * @param visible Determines whether the PopupMenu is clickable or not.
		 */
		virtual void AddMenuItem(const FakeString & name, int32 id, int32 position, bool visible = true) = 0;

		/**
		 *
		 * Adds a new Seperator to the Menu.
		 *
		 */
		virtual void AddSeperator() = 0;

		/**
		 *
		 * Adds another Menu as a Submenu to the Menu instance.
		 *
		 * @param other The SubMenu that should be added to the Menu.
		 */
		virtual void AddSubMenu(const FakeRef<FakePopupMenu> &other) = 0;

		/**
		 *
		 * This function displays the Rightclick Menu if the right mouse button is pressed.
		 *
		 */
		virtual void Show() = 0;

		/**
		 *
		 * Returns the platform specific PopupMenu handle that contains the PopupMenu if any exists.
		 *
		 * @return Returns the platform specific PopupMenu handle that contains the PopupMenu if any exists.
		 */
		virtual void *GetPopupMenuHandle() = 0;

		/**
		 *
		 * Returns the platform specific PopupMenu handle that contains the PopupMenu if any exists.
		 *
		 * @return Returns the platform specific PopupMenu handle that contains the PopupMenu if any exists.
		 */
		virtual void *GetPopupMenuHandle() const = 0;

		/**
		 *
		 * Returns the Root name of the PopupMenu.
		 *
		 * @return Returns the Root name of the PopupMenu.
		 */
		virtual FakeString &GetName() = 0;

		/**
		 *
		 * Returns the Root name of the PopupMenu.
		 *
		 * @return Returns the Root name of the PopupMenu.
		 */
		virtual const FakeString &GetName() const = 0;

		/**
		 *
		 * Creates a new platform specific PopupMenu class.
		 *
		 * @param name The name that should be displayed as the root name for the PopupMenu.
		 * @return Returns a new platform specific PopupMenu class instance.
		 */
		static FakeRef<FakePopupMenu> Create(const FakeString &name);
	};
