/*****************************************************************
 * \file   FakeKeyCodes.h
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

typedef enum class FakeKeyCode : uint16
	{
	/* Printable keys */
	SPACE = 32,
	APOSTROPHE = 39,  /* ' */
	COMMA = 44,  /* , */
	MINUS = 45,  /* - */
	PERIOD = 46,  /* . */
	SLASH = 47,  /* / */
	SEMICOLON = 59,  /* ; */
	EQUAL = 61,  /* = */
	LEFT_BRACKET = 91,  /* [ */
	BACKSLASH = 92,  /* \ */
	RIGHT_BRACKET = 93,  /* ] */
	GRAVE_ACCENT = 96,  /* ` */
	WORLD_1 = 161, /* non-US #1 */
	WORLD_2 = 162, /* non-US #2 */

	K_0 = 48,
	K_1 = 49,
	K_2 = 50,
	K_3 = 51,
	K_4 = 52,
	K_5 = 53,
	K_6 = 54,
	K_7 = 55,
	K_8 = 56,
	K_9 = 57,

	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,

	/* Function keys */
	ESCAPE = 256,
	ENTER = 257,
	TAB = 258,
	BACKSPACE = 259,
	INSERT = 260,
	KEY_DELETE = 261,
	RIGHT = 262,
	LEFT = 263,
	DOWN = 264,
	UP = 265,
	PAGE_UP = 266,
	PAGE_DOWN = 267,
	HOME = 268,
	END = 269,
	CAPS_LOCK = 280,
	SCROLL_LOCK = 281,
	NUM_LOCK = 282,
	PRINT_SCREEN = 283,
	PAUSE = 284,
	F1 = 290,
	F2 = 291,
	F3 = 292,
	F4 = 293,
	F5 = 294,
	F6 = 295,
	F7 = 296,
	F8 = 297,
	F9 = 298,
	F10 = 299,
	F11 = 300,
	F12 = 301,
	F13 = 302,
	F14 = 303,
	F15 = 304,
	F16 = 305,
	F17 = 306,
	F18 = 307,
	F19 = 308,
	F20 = 309,
	F21 = 310,
	F22 = 311,
	F23 = 312,
	F24 = 313,
	F25 = 314,

	KP_0 = 320,
	KP_1 = 321,
	KP_2 = 322,
	KP_3 = 323,
	KP_4 = 324,
	KP_5 = 325,
	KP_6 = 326,
	KP_7 = 327,
	KP_8 = 328,
	KP_9 = 329,
	KP_DECIMAL = 330,
	KP_DIVIDE = 331,
	KP_MULTIPLY = 332,
	KP_SUBTRACT = 333,
	KP_ADD = 334,
	KP_ENTER = 335,
	KP_EQUAL = 336,
	LEFT_SHIFT = 340,
	LEFT_CONTROL = 341,
	LEFT_ALT = 342,
	LEFT_SUPER = 343,
	RIGHT_SHIFT = 344,
	RIGHT_CONTROL = 345,
	RIGHT_ALT = 346,
	RIGHT_SUPER = 347,
	MENU = 348
	} FakeKey;

inline std::ostream &operator<<(std::ostream &stream, FakeKeyCode code)
	{
	return stream << static_cast<int32>(code);
	}


/* Printable keys */
#define FAKE_KEY_SPACE              ::FakeKey::SPACE
#define FAKE_KEY_APOSTROPHE         ::FakeKey::APOSTROPHE   /* ' */
#define FAKE_KEY_COMMA              ::FakeKey::COMMA		/* , */
#define FAKE_KEY_MINUS              ::FakeKey::MINUS		/* - */
#define FAKE_KEY_PERIOD             ::FakeKey::PERIOD       /* . */
#define FAKE_KEY_SLASH              ::FakeKey::SLASH        /* / */
#define FAKE_KEY_0                  ::FakeKey::K_0
#define FAKE_KEY_1                  ::FakeKey::K_1
#define FAKE_KEY_2                  ::FakeKey::K_2
#define FAKE_KEY_3                  ::FakeKey::K_3
#define FAKE_KEY_4                  ::FakeKey::K_4
#define FAKE_KEY_5                  ::FakeKey::K_5
#define FAKE_KEY_6                  ::FakeKey::K_6
#define FAKE_KEY_7                  ::FakeKey::K_7
#define FAKE_KEY_8                  ::FakeKey::K_8
#define FAKE_KEY_9                  ::FakeKey::K_9
#define FAKE_KEY_SEMICOLON          ::FakeKey::SEMICOLON     /* ; */
#define FAKE_KEY_EQUAL              ::FakeKey::EQUAL         /* = */
#define FAKE_KEY_A                  ::FakeKey::A
#define FAKE_KEY_B                  ::FakeKey::B
#define FAKE_KEY_C                  ::FakeKey::C
#define FAKE_KEY_D                  ::FakeKey::D
#define FAKE_KEY_E                  ::FakeKey::E
#define FAKE_KEY_F                  ::FakeKey::F
#define FAKE_KEY_G                  ::FakeKey::G
#define FAKE_KEY_H                  ::FakeKey::H
#define FAKE_KEY_I                  ::FakeKey::I
#define FAKE_KEY_J                  ::FakeKey::J
#define FAKE_KEY_K                  ::FakeKey::K
#define FAKE_KEY_L                  ::FakeKey::L
#define FAKE_KEY_M                  ::FakeKey::M
#define FAKE_KEY_N                  ::FakeKey::N
#define FAKE_KEY_O                  ::FakeKey::O
#define FAKE_KEY_P                  ::FakeKey::P
#define FAKE_KEY_Q                  ::FakeKey::Q
#define FAKE_KEY_R                  ::FakeKey::R
#define FAKE_KEY_S                  ::FakeKey::S
#define FAKE_KEY_T                  ::FakeKey::T
#define FAKE_KEY_U                  ::FakeKey::U
#define FAKE_KEY_V                  ::FakeKey::V
#define FAKE_KEY_W                  ::FakeKey::W
#define FAKE_KEY_X                  ::FakeKey::X
#define FAKE_KEY_Y                  ::FakeKey::Y
#define FAKE_KEY_Z                  ::FakeKey::Z
#define FAKE_KEY_LEFT_BRACKET       ::FakeKey::LEFT_BRACKET  /* [ */
#define FAKE_KEY_BACKSLASH          ::FakeKey::BACKSLASH  /* \ */
#define FAKE_KEY_RIGHT_BRACKET      ::FakeKey::RIGHT_BRACKET  /* ] */
#define FAKE_KEY_GRAVE_ACCENT       ::FakeKey::GRAVE_ACCENT  /* ` */
#define FAKE_KEY_WORLD_1            ::FakeKey::WORLD_1 /* non-US #1 */
#define FAKE_KEY_WORLD_2            ::FakeKey::WORLD_2 /* non-US #2 */

/* Function keys */
#define FAKE_KEY_ESCAPE             ::FakeKey::ESCAPE
#define FAKE_KEY_ENTER              ::FakeKey::ENTER
#define FAKE_KEY_TAB                ::FakeKey::TAB
#define FAKE_KEY_BACKSPACE          ::FakeKey::BACKSPACE
#define FAKE_KEY_INSERT             ::FakeKey::INSERT
#define FAKE_KEY_DELETE             ::FakeKey::KEY_DELETE
#define FAKE_KEY_RIGHT              ::FakeKey::RIGHT
#define FAKE_KEY_LEFT               ::FakeKey::LEFT
#define FAKE_KEY_DOWN               ::FakeKey::DOWN
#define FAKE_KEY_UP                 ::FakeKey::UP
#define FAKE_KEY_PAGE_UP            ::FakeKey::PAGE_UP
#define FAKE_KEY_PAGE_DOWN          ::FakeKey::PAGE_DOWN
#define FAKE_KEY_HOME               ::FakeKey::HOME
#define FAKE_KEY_END                ::FakeKey::END
#define FAKE_KEY_CAPS_LOCK          ::FakeKey::CAPS_LOCK
#define FAKE_KEY_SCROLL_LOCK        ::FakeKey::SCROLL_LOCK
#define FAKE_KEY_NUM_LOCK           ::FakeKey::NUM_LOCK
#define FAKE_KEY_PRINT_SCREEN       ::FakeKey::PRINT_SCREEN
#define FAKE_KEY_PAUSE              ::FakeKey::PAUSE
#define FAKE_KEY_F1                 ::FakeKey::F1
#define FAKE_KEY_F2                 ::FakeKey::F2
#define FAKE_KEY_F3                 ::FakeKey::F3
#define FAKE_KEY_F4                 ::FakeKey::F4
#define FAKE_KEY_F5                 ::FakeKey::F5
#define FAKE_KEY_F6                 ::FakeKey::F6
#define FAKE_KEY_F7                 ::FakeKey::F7
#define FAKE_KEY_F8                 ::FakeKey::F8
#define FAKE_KEY_F9                 ::FakeKey::F9
#define FAKE_KEY_F10                ::FakeKey::F10
#define FAKE_KEY_F11                ::FakeKey::F11
#define FAKE_KEY_F12                ::FakeKey::F12
#define FAKE_KEY_F13                ::FakeKey::F13
#define FAKE_KEY_F14                ::FakeKey::F14
#define FAKE_KEY_F15                ::FakeKey::F15
#define FAKE_KEY_F16                ::FakeKey::F16
#define FAKE_KEY_F17                ::FakeKey::F17
#define FAKE_KEY_F18                ::FakeKey::F18
#define FAKE_KEY_F19                ::FakeKey::F19
#define FAKE_KEY_F20                ::FakeKey::F20
#define FAKE_KEY_F21                ::FakeKey::F21
#define FAKE_KEY_F22                ::FakeKey::F22
#define FAKE_KEY_F23                ::FakeKey::F23
#define FAKE_KEY_F24                ::FakeKey::F24
#define FAKE_KEY_F25                ::FakeKey::F25
#define FAKE_KEY_KP_0               ::FakeKey::KP_0
#define FAKE_KEY_KP_1               ::FakeKey::KP_1
#define FAKE_KEY_KP_2               ::FakeKey::KP_2
#define FAKE_KEY_KP_3               ::FakeKey::KP_3
#define FAKE_KEY_KP_4               ::FakeKey::KP_4
#define FAKE_KEY_KP_5               ::FakeKey::KP_5
#define FAKE_KEY_KP_6               ::FakeKey::KP_6
#define FAKE_KEY_KP_7               ::FakeKey::KP_7
#define FAKE_KEY_KP_8               ::FakeKey::KP_8
#define FAKE_KEY_KP_9               ::FakeKey::KP_9
#define FAKE_KEY_KP_DECIMAL         ::FakeKey::KP_DECIMAL
#define FAKE_KEY_KP_DIVIDE          ::FakeKey::KP_DIVIDE
#define FAKE_KEY_KP_MULTIPLY        ::FakeKey::KP_MULTIPLY
#define FAKE_KEY_KP_SUBTRACT        ::FakeKey::KP_SUBTRACT
#define FAKE_KEY_KP_ADD             ::FakeKey::KP_ADD
#define FAKE_KEY_KP_ENTER           ::FakeKey::KP_ENTER
#define FAKE_KEY_KP_EQUAL           ::FakeKey::KP_EQUAL
#define FAKE_KEY_LEFT_SHIFT         ::FakeKey::LEFT_SHIFT
#define FAKE_KEY_LEFT_CONTROL       ::FakeKey::LEFT_CONTROL
#define FAKE_KEY_LEFT_ALT           ::FakeKey::LEFT_ALT
#define FAKE_KEY_LEFT_SUPER         ::FakeKey::LEFT_SUPER
#define FAKE_KEY_RIGHT_SHIFT        ::FakeKey::RIGHT_SHIFT
#define FAKE_KEY_RIGHT_CONTROL      ::FakeKey::RIGHT_CONTROL
#define FAKE_KEY_RIGHT_ALT          ::FakeKey::RIGHT_ALT
#define FAKE_KEY_RIGHT_SUPER        ::FakeKey::RIGHT_SUPER
#define FAKE_KEY_MENU               ::FakeKey::MENU
