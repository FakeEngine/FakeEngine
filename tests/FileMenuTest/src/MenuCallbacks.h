/*****************************************************************
 * \file   MenuCallbacks.h
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

#include "FileMenuIDs.h"

class FileMenuCallbacks : public FakeLayer
	{
	private:

		bool OnFileMenu(const FakeFileMenuEvent &e)
			{
			FAKE_LOG_TRACE("%s", *e.ToString());

			switch (e.GetID())
				{
				case FILE_MENU_NEW:
					OnNewProject();
					break;

				case FILE_MENU_OPEN:
					OnOpenProject();
					break;

				case FILE_MENU_SAVE:
					OnProjectSave();
					break;

				case FILE_MENU_SAVE_AS:
					OnProjectSaveAs();
					break;

				case FILE_MENU_SETTINGS:
					OnSettings();
					break;

				case FILE_MENU_QUIT:
					OnQuit();
					break;

				case FILE_MENU_UNDO:
					OnUndo();
					break;

				case FILE_MENU_REDO:
					OnRedo();
					break;

				case FILE_MENU_CUT:
					OnCut();
					break;

				case FILE_MENU_COPY:
					OnCopy();
					break;

				case FILE_MENU_PASTE:
					OnPaste();
					break;

				case FILE_MENU_INFO:
					OnInfo();
					break;

				case FILE_MENU_HELP:
					OnHelp();
					break;

				case FILE_MENU_ABOUT:
					OnAbout();
					break;
				}

			return true;
			}

		bool OnKeyPressed(const FakeKeyPressedEvent &e)
			{
			// CTRL+Q
			if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_CONTROL) && e.GetKeyCode() == FakeKeyCode::Q)
				{
				OnQuit();
				}
			// CTRL+Shift+S
			else if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_CONTROL) && FakeInput::IsKeyPressed(FakeKeyCode::LEFT_SHIFT) && e.GetKeyCode() == FakeKeyCode::S)
				{
				OnProjectSaveAs();
				}
			// CTRL+S
			else if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_CONTROL) && e.GetKeyCode() == FakeKeyCode::S)
				{
				OnProjectSave();
				}
			// CTRL+O
			else if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_CONTROL) && e.GetKeyCode() == FakeKeyCode::O)
				{
				OnOpenProject();
				}
			// CTRL+N
			else if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_CONTROL) && e.GetKeyCode() == FakeKeyCode::N)
				{
				OnNewProject();
				}
			// CTRL+Z
			else if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_CONTROL) && e.GetKeyCode() == FakeKeyCode::Z)
				{
				OnUndo();
				}
			// CTRL+Y
			else if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_CONTROL) && e.GetKeyCode() == FakeKeyCode::Y)
				{
				OnRedo();
				}
			// CTRL+X
			else if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_CONTROL) && e.GetKeyCode() == FakeKeyCode::X)
				{
				OnCut();
				}
			// CTRL+C
			else if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_CONTROL) && e.GetKeyCode() == FakeKeyCode::C)
				{
				OnCopy();
				}
			// CTRL+V
			else if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_CONTROL) && e.GetKeyCode() == FakeKeyCode::V)
				{
				OnPaste();
				}
			// CTRL+H
			else if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_CONTROL) && e.GetKeyCode() == FakeKeyCode::H)
				{
				OnHelp();
				}

			return true;
			}

		void OnNewProject()
			{
			FakeApplication::Get().GetWindow().ShowMessageBox("FileMenu Demo", "New Project", FakeWindowMessageButtonType::BTN_OK);
			}

		void OnOpenProject()
			{
			FakeRef<FakeFileDialogue> fd = FakeFileDialogue::Create();
			FakeString path = fd->SelectFile();
			std::cout << "YOUR PATH: " << path << std::endl;
			}

		void OnProjectSave()
			{
			FakeApplication::Get().GetWindow().ShowMessageBox("FileMenu Demo", "Save Project", FakeWindowMessageButtonType::BTN_OK);
			}

		void OnProjectSaveAs()
			{
			FakeRef<FakeFileDialogue> fd = FakeFileDialogue::Create();
			FakeString path = fd->SaveFile();
			std::cout << "YOUR PATH: " << path << std::endl;
			}

		void OnSettings()
			{
			FakeApplication::Get().GetWindow().ShowMessageBox("FileMenu Demo", "Setting", FakeWindowMessageButtonType::BTN_OK);
			}

		void OnQuit()
			{
			FakeApplication::Get().CloseApplication();
			}

		void OnUndo()
			{
			FakeApplication::Get().GetWindow().ShowMessageBox("FileMenu Demo", "Undo", FakeWindowMessageButtonType::BTN_OK);
			}

		void OnRedo()
			{
			FakeApplication::Get().GetWindow().ShowMessageBox("FileMenu Demo", "Redo", FakeWindowMessageButtonType::BTN_OK);
			}

		void OnCut()
			{
			FakeApplication::Get().GetWindow().ShowMessageBox("FileMenu Demo", "Cut", FakeWindowMessageButtonType::BTN_OK);
			}

		void OnCopy()
			{
			FakeApplication::Get().GetWindow().ShowMessageBox("FileMenu Demo", "Copy", FakeWindowMessageButtonType::BTN_OK);
			}

		void OnPaste()
			{
			FakeApplication::Get().GetWindow().ShowMessageBox("FileMenu Demo", "Paste", FakeWindowMessageButtonType::BTN_OK);
			}

		void OnInfo()
			{
			FakeApplication::Get().GetWindow().ShowMessageBox("FileMenu Demo", "Info", FakeWindowMessageButtonType::BTN_OK);
			}

		void OnHelp()
			{
			FakeApplication::Get().GetWindow().ShowMessageBox("FileMenu Demo", "Help Menu", FakeWindowMessageButtonType::BTN_OK);
			}

		void OnAbout()
			{
			FakeVirtualFileSystem::Get()->OpenInBrowser("https://www.fake-engine.com/");
			}

	public:

		virtual void OnAttach() override
			{
			}

		virtual void OnDetach() override
			{
			}

		virtual void OnEvent(FakeEvent &e) override
			{
			FakeEventDispatcher dispatcher(e);
			dispatcher.Dispatch<FakeFileMenuEvent>(FAKE_BIND_EVENT_FUNCTION(FileMenuCallbacks::OnFileMenu));
			dispatcher.Dispatch<FakeKeyPressedEvent>(FAKE_BIND_EVENT_FUNCTION(FileMenuCallbacks::OnKeyPressed));
			}

		virtual void OnRender(FakeTimeStep ts) override
			{
			}
	};
