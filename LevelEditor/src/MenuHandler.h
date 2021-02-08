/*****************************************************************
 * \file   MenuHandler.h
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

#include "LevelEditorFileMenuIDs.h"

class MenuHandler : public FakeLayer
	{
	private:

		bool OnFileMenu(const FakeFileMenuEvent &e)
			{
			switch (e.GetID())
				{
				case FILE_MENU_QUIT:
					OnQuit();
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

			return true;
			}

		void OnQuit()
			{
			FakeApplication::Get().CloseApplication();
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
			dispatcher.Dispatch<FakeFileMenuEvent>(FAKE_BIND_EVENT_FUNCTION(MenuHandler::OnFileMenu));
			dispatcher.Dispatch<FakeKeyPressedEvent>(FAKE_BIND_EVENT_FUNCTION(MenuHandler::OnKeyPressed));
			}

		virtual void OnRender(FakeTimeStep ts) override
			{
			}
	};
