/*****************************************************************
 * \file   FakeWindowsFileMenuBar.h
 * \brief  
 * 
 * \author Can Karka
 * \date   January 2021
 * 
 * 
 *********************************************************************/

#pragma once

#include <Windows.h>

#include "Engine/Core/Window/FakeFileMenuBar.h"

/**
 *
 * This class represents a windows specific FileMenuBar that holds all FileMenu entries.
 *
 */
class FAKE_API FakeWindowsFileMenuBar : public FakeFileMenuBar
	{
	private:
		HMENU Menubar;

	public:

		/**
		 *
		 * constructor that initializes the FileMenubar.
		 *
		 */
		FakeWindowsFileMenuBar();

		/**
		 *
		 * virtual destructor.
		 *
		 */
		virtual ~FakeWindowsFileMenuBar();

		/**
		 *
		 * Adds a new FileMenu to the Menubar.
		 *
		 * @param menu The menu that should be added.
		 */
		virtual void AddMenu(const FakeRef<FakeFileMenu> &menu) override;

		/**
		 *
		 * Removes a FileMenu from the Menubar.
		 *
		 * @param menu The menu that should be removed.
		 */
		virtual void RemoveMenu(const FakeRef<FakeFileMenu> &menu) override;

		/**
		 *
		 * Returns the windows specific Menubar handle that contains all FileMenus if any exists.
		 *
		 * @return Returns the windows specific Menubar handle that contains all FileMenus if any exists.
		 */
		virtual void *GetNativeMenuBar() override;

		/**
		 *
		 * Returns the windows specific Menubar handle that contains all FileMenus if any exists.
		 *
		 * @return Returns the windows specific Menubar handle that contains all FileMenus if any exists.
		 */
		virtual void *GetNativeMenuBar() const override;
	};
