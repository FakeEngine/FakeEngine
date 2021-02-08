/*****************************************************************
 * \file   FakeMouseButtonCodes.h
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

#include <iostream>
#include "Engine/Core/DataTypes/FakeBaseTypes.h"

typedef enum class FakeMouseButtonCode : uint16
	{
	BUTTON_1 = 0,
	BUTTON_2 = 1,
	BUTTON_3 = 2,
	BUTTON_4 = 3,
	BUTTON_5 = 4,
	BUTTON_6 = 5,
	BUTTON_7 = 6,
	BUTTON_8 = 7,
	BUTTON_LAST = 7,
	BUTTON_LEFT = 0,
	BUTTON_RIGHT = 1,
	BUTTON_MIDDLE = 2
	} FakeMouse;

inline std::ostream &operator<<(std::ostream &stream, FakeMouseButtonCode code)
	{
	return stream << static_cast<int32>(code);
	}

#define FAKE_MOUSE_BUTTON_1 ::FakeMouse::BUTTON_1
#define FAKE_MOUSE_BUTTON_2 ::FakeMouse::BUTTON_2
#define FAKE_MOUSE_BUTTON_3 ::FakeMouse::BUTTON_3
#define FAKE_MOUSE_BUTTON_4 ::FakeMouse::BUTTON_4
#define FAKE_MOUSE_BUTTON_5 ::FakeMouse::BUTTON_5
#define FAKE_MOUSE_BUTTON_6 ::FakeMouse::BUTTON_6
#define FAKE_MOUSE_BUTTON_7 ::FakeMouse::BUTTON_7
#define FAKE_MOUSE_BUTTON_8 ::FakeMouse::BUTTON_8
#define FAKE_MOUSE_BUTTON_LAST ::FakeMouse::BUTTON_LAST
#define FAKE_MOUSE_BUTTON_LEFT ::FakeMouse::BUTTON_LEFT
#define FAKE_MOUSE_BUTTON_RIGHT ::FakeMouse::BUTTON_RIGHT
#define FAKE_MOUSE_BUTTON_MIDDLE ::FakeMouse::BUTTON_MIDDLE
