/*****************************************************************
 * \file   FakePopupMenuItem.h
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

#include "FakePch.h"

/**
 *
 * This class represents a FilePopupMenuItem that contains the Data needed for a file popup menu entry.
 *
 */
struct FAKE_API FakePopupMenuItem : public FakeRefCounted
	{
	FakeString Name = "DefaultPopupMenuItem";
	int32 ID = 0;
	int32 Position = 0;
	bool Visible = true;
	bool Seperator = false;

	FakePopupMenuItem() = default;

	FakePopupMenuItem(const FakeString &name, int32 id, int32 position, bool visible = true, bool seperator = false)
		: Name(name), ID(id), Position(position), Visible(visible), Seperator(seperator)
		{
		}

	FakePopupMenuItem(const FakePopupMenuItem &other)
		: Name(other.Name), ID(other.ID), Position(other.Position), Visible(other.Visible), Seperator(other.Seperator)
		{
		}
	};

