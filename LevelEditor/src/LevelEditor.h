/*****************************************************************
 * \file   LevelEditor.h
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

#include "LevelEditorLayer.h"
#include "LevelEditorFileMenuIDs.h"
#include "MenuHandler.h"

class LevelEditor : public FakeApplication
	{
	private:
		FakeRef<FakeFileMenuBar> MenuBar;

	public:

		LevelEditor()
			: FakeApplication("FakeEngine LevelEditor", 1280, 720)
			{
			}

		virtual void OnInit() override
			{
			PushLayer(new LevelEditorLayer());
			PushLayer(new MenuHandler());

			MenuBar = FakeFileMenuBar::Create();

			// File Menu
			FakeRef<FakeFileMenu> fileMenu = FakeFileMenu::Create("File");
			
			FakeRef<FakeFileMenu> fileMenuNew = FakeFileMenu::Create("New");
			fileMenuNew->AddMenuItem("New Scene\tCtrl+N", FILE_MENU_NEW_SCENE);
			fileMenuNew->AddMenuItem("New Project", FILE_MENU_NEW_PROJECT);

			FakeRef<FakeFileMenu> fileMenuOpen = FakeFileMenu::Create("Open");
			fileMenuOpen->AddMenuItem("Open Scene...\tCtrl+O", FILE_MENU_OPEN_SCENE);
			fileMenuOpen->AddMenuItem("Open Project...", FILE_MENU_OPEN_PROJECT);

			fileMenu->AddSubMenu(fileMenuNew);
			fileMenu->AddMenuSeperator();
			fileMenu->AddSubMenu(fileMenuOpen);
			fileMenu->AddMenuSeperator();
			fileMenu->AddMenuItem("Save Scenes\tCtrl+S", FILE_MENU_SAVE_SCENE);
			fileMenu->AddMenuItem("Save Scene as...\tCtrl+Shift+S", FILE_MENU_SAVE_SCENE_AS);
			fileMenu->AddMenuItem("Save Project...", FILE_MENU_SAVE_PROJECT);
			fileMenu->AddMenuSeperator();
			fileMenu->AddMenuItem("Settings...", FILE_MENU_SCENE_SETTINGS);
			fileMenu->AddMenuItem("Quit\tCtrl+Q", FILE_MENU_QUIT);
			MenuBar->AddMenu(fileMenu);

			// Edit Menu
			FakeRef<FakeFileMenu> editMenu = FakeFileMenu::Create("Edit");
			editMenu->AddMenuItem("Undo\tCtrl+Z", FILE_MENU_UNDO);
			editMenu->AddMenuItem("Redo\tCtrl+Y", FILE_MENU_REDO);
			editMenu->AddMenuSeperator();
			editMenu->AddMenuItem("Cut\tCtrl+X", FILE_MENU_CUT);
			editMenu->AddMenuItem("Copy\tCtrl+C", FILE_MENU_COPY);
			editMenu->AddMenuItem("Paste\tCtrl+V", FILE_MENU_PASTE);
			editMenu->AddMenuSeperator();
			editMenu->AddMenuItem("Duplicate\tCtrl+D", FILE_MENU_DUPLICATE);
			editMenu->AddMenuItem("Delete\tCtrl+Del", FILE_MENU_DELETE);
			editMenu->AddMenuSeperator();
			MenuBar->AddMenu(editMenu);

			// Assets Menu
			FakeRef<FakeFileMenu> assetMenu = FakeFileMenu::Create("Assets");
			FakeRef<FakeFileMenu> assetCreateMenu = FakeFileMenu::Create("Create");
			assetCreateMenu->AddMenuItem("Folder", FILE_MENU_CREATE_FOLDER);
			assetCreateMenu->AddMenuItem("C# Script", FILE_MENU_CREATE_CSSCRIPT);
			assetCreateMenu->AddMenuItem("Javascript", FILE_MENU_CREATE_JSCRIPT);
			assetCreateMenu->AddMenuItem("Lua Script", FILE_MENU_CREATE_LUASCRIPT);
			assetCreateMenu->AddMenuSeperator();
			assetCreateMenu->AddMenuItem("Scene", FILE_MENU_CREATE_SCENE);
			assetCreateMenu->AddMenuItem("Model", FILE_MENU_CREATE_MODEL);
			assetCreateMenu->AddMenuItem("Shader", FILE_MENU_CREATE_SHADER);
			assetCreateMenu->AddMenuItem("Material", FILE_MENU_CREATE_MATERIAL);
			assetMenu->AddSubMenu(assetCreateMenu);
			assetMenu->AddMenuItem("Show in Explorer", FILE_MENU_SHOW_EXPLORER);
			assetMenu->AddMenuItem("Refresh\tCtrl+R", FILE_MENU_REFRESH);
			assetMenu->AddMenuItem("Reimport", FILE_MENU_REIMPORT);
			assetMenu->AddMenuItem("Reimport all", FILE_MENU_REIMPORT_ALL);
			assetMenu->AddMenuItem("Open C# Project", FILE_MENU_OPEN_CS_PROJECT);
			MenuBar->AddMenu(assetMenu);

			// GameObject Menu
			FakeRef<FakeFileMenu> gameObjectMenu = FakeFileMenu::Create("GameObject");
			gameObjectMenu->AddMenuItem("Create Empty object", FILE_MENU_GAMEOBJECT_CREATE_EMPTY);
			gameObjectMenu->AddMenuItem("Create Camera", FILE_MENU_GAMEOBJECT_CREATE_CAMERA);
			gameObjectMenu->AddMenuItem("Create Cube", FILE_MENU_GAMEOBJECT_CREATE_CUBE);
			gameObjectMenu->AddMenuItem("Create Plane", FILE_MENU_GAMEOBJECT_CREATE_PLANE);
			gameObjectMenu->AddMenuItem("Create Sphere", FILE_MENU_GAMEOBJECT_CREATE_SPHERE);
			gameObjectMenu->AddMenuItem("Create Cylinder", FILE_MENU_GAMEOBJECT_CREATE_CYLINDER);
			gameObjectMenu->AddMenuItem("Create Text", FILE_MENU_GAMEOBJECT_CREATE_TEXT);
			MenuBar->AddMenu(gameObjectMenu);

			// Window Menu


			// Help Menu

			FakeApplication::Get().GetWindow().Maximize(true);
			FakeApplication::Get().GetWindow().SetMenuBar(MenuBar);
			}

		virtual void OnShutdown() override
			{
			}
	};
