/*****************************************************************
 * \file   FileMenuTest.h
 * \brief  
 * 
 * \author Can Karka
 * \date   February 2021
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

#include <Fake.h>

#include "MenuCallbacks.h"
#include "FileMenuIDs.h"

class FileMenuTest : public FakeApplication
	{
	private:
		FakeRef<FakeFileMenu> FileMenu;
		FakeRef<FakeFileMenu> EditMenu;
		FakeRef<FakeFileMenu> HelpMenu;


	public:

		FileMenuTest()
			: FakeApplication("FakeEngine FileMenuTest", 1280, 720)
			{
			}

		virtual void OnInit() override
			{
			PushLayer(new FileMenuCallbacks());

			FakeRef<FakeFileMenuBar> menuBar = FakeFileMenuBar::Create();

			FileMenu = FakeFileMenu::Create("File");
			FileMenu->AddMenuItem("New project\tCtrl+N", FILE_MENU_NEW);
			FileMenu->AddMenuItem("Open project...\tCtrl+O", FILE_MENU_OPEN);
			FileMenu->AddMenuItem("Save project\tCtrl+S", FILE_MENU_SAVE);
			FileMenu->AddMenuItem("Save project as...\tCtrl+Shift+S", FILE_MENU_SAVE_AS);
			FileMenu->AddMenuSeperator();
			FileMenu->AddMenuItem("Settings", FILE_MENU_SETTINGS);
			FileMenu->AddMenuItem("Quit\tCtrl+Q", FILE_MENU_QUIT);

			EditMenu = FakeFileMenu::Create("Edit");
			EditMenu->AddMenuItem("Undo\tCtrl+Z", FILE_MENU_UNDO);
			EditMenu->AddMenuItem("Redo\tCtrl+Y", FILE_MENU_REDO);
			EditMenu->AddMenuSeperator();
			EditMenu->AddMenuItem("Cut\tCtrl+X", FILE_MENU_CUT);
			EditMenu->AddMenuItem("Copy\tCtrl+C", FILE_MENU_COPY);
			EditMenu->AddMenuItem("Paste\tCtrl+V", FILE_MENU_PASTE);

			HelpMenu = FakeFileMenu::Create("Help");
			HelpMenu->AddMenuItem("About FakeEngine...", FILE_MENU_ABOUT);
			HelpMenu->AddMenuItem("Need Help?\tCtrl+H", FILE_MENU_HELP);
			HelpMenu->AddMenuItem("About", FILE_MENU_INFO);

			menuBar->AddMenu(FileMenu);
			menuBar->AddMenu(EditMenu);
			menuBar->AddMenu(HelpMenu);
			FakeApplication::Get().GetWindow().SetMenuBar(menuBar);
			}

		virtual void OnShutdown() override
			{

			}
	};
