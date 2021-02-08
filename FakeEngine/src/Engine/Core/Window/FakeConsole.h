/*****************************************************************
 * \file   FakeConsole.h
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

#include "Engine/Core/FakeCore.h"
#include "Engine/Core/Defines/FakeConsole.h"
#include "Engine/Core/DataTypes/FakeString.h"

enum class FakeConsoleTextStyle
	{
	NONE = 0,
	BOLD = 1,
	FAINT = 2,
	ITALIC = 3,
	UNDERLINE = 4,
	SLOW_BLINK = 5,
	RAPID_BLINK = 6,
	REVERSE = 7,
	};

enum class FakeConsoleForeground
	{
	NONE = 0,
	BLACK,
	DARK_RED,
	DARK_GREEN,
	DARK_YELLOW,
	DARK_BLUE,
	DARK_MAGENTA,
	DARK_CYAN,
	GRAY,
	DARK_GRAY,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
	};

enum class FakeConsoleBackground
	{
	NONE = 0,
	BLACK,
	DARK_RED,
	DARK_GREEN,
	DARK_YELLOW,
	DARK_BLUE,
	DARK_MAGENTA,
	DARK_CYAN,
	GRAY,
	DARK_GRAY,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
	};

/**
 * 
 * .
 * 
 */
class FAKE_API FakeConsole : public FakeRefCounted
	{
	public:

		/**
		 * 
		 * .
		 * 
		 * @param color
		 */
		virtual void SetColor(int32 color = 0x07) = 0;

		/**
		 * 
		 * .
		 * 
		 */
		virtual void EnableVirtualTerminalProcessing() = 0;

		/**
		 * 
		 * .
		 * 
		 */
		virtual void ResetTerminalFormat() = 0;

		/**
		 * 
		 * .
		 * 
		 * @param foreground
		 * @param background
		 * @param styles
		 */
		virtual void SetVirtualTerminalFormat(FakeConsoleForeground foreground, FakeConsoleBackground background, std::set<FakeConsoleTextStyle> styles) = 0;

		/**
		 * 
		 * .
		 * 
		 */
		virtual void Clear() = 0;

		/**
		 * 
		 * .
		 * 
		 * @param foreground
		 * @param background
		 * @param styles
		 */
		virtual void Write(const FakeString &str, FakeConsoleForeground foreground = FakeConsoleForeground::NONE, FakeConsoleBackground background = FakeConsoleBackground::NONE, std::set<FakeConsoleTextStyle> styles = {}) = 0;

		/**
		 * 
		 * .
		 * 
		 * @param foreground
		 * @param background
		 * @param styles
		 */
		virtual void WriteLine(const FakeString &str, FakeConsoleForeground foreground = FakeConsoleForeground::NONE, FakeConsoleBackground background = FakeConsoleBackground::NONE, std::set<FakeConsoleTextStyle> styles = {}) = 0;

		/**
		 * 
		 * .
		 * 
		 */
		virtual void WriteLine() = 0;

		/**
		 * 
		 * .
		 * 
		 */
		static FakeRef<FakeConsole> Create();
	};
