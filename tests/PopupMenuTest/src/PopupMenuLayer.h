/*****************************************************************
 * \file   PopupMenuLayer.h
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

#include "PopupMenuIDs.h"

class PopupMenuLayer : public FakeLayer
	{
	private:

		FakeRef<FakePopupMenu> PopupMenu;
		FakeRef<FakePopupMenu> SecondMenu;

		bool OnFileMenuEvent(const FakeFileMenuEvent &e)
			{
			FAKE_LOG_TRACE("%s", *e.ToString());
			return true;
			}

	public:

		virtual void OnAttach() override
			{
			PopupMenu = FakePopupMenu::Create("Primary Menu");
			SecondMenu = FakePopupMenu::Create("SubMenu");

			PopupMenu->AddMenuItem("One Element", POPUP_MENU_ELEMENT_ONE, 1);
			SecondMenu->AddMenuItem("SubMenuItem", POPUP_MENU_ELEMENT_TWO, 1);
			SecondMenu->AddMenuItem("AnotherItem", POPUP_MENU_ELEMENT_THREE, 2);

			PopupMenu->AddSubMenu(SecondMenu);
			}

		virtual void OnDetach() override
			{
			}

		virtual void OnEvent(FakeEvent &e) override
			{
			FakeEventDispatcher dispatcher(e);
			dispatcher.Dispatch<FakeFileMenuEvent>(FAKE_BIND_EVENT_FUNCTION(PopupMenuLayer::OnFileMenuEvent));
			}

		virtual void OnRender(FakeTimeStep ts) override
			{
			PopupMenu->Show();
			}
	};
