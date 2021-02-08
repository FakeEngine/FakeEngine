/*****************************************************************
 * \file   FakeLinuxConsole.h
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

#include "Engine/Core/Window/FakeConsole.h"

/**
 * 
 * .
 * 
 */
class FAKE_API FakeLinuxConsole : public FakeConsole
	{
	private:

		/**
		 *
		 * .
		 *
		 * @param foreground
		 * @return
		 */
		int32 ConvertForeground(FakeConsoleForeground foreground);

		/**
		 *
		 * .
		 *
		 * @param background
		 * @return
		 */
		int32 ConvertBackground(FakeConsoleBackground background);

	public:

		/**
		 *
		 * .
		 *
		 * @param color
		 */
		virtual void SetColor(int32 color = 0x07) override;

		/**
		 *
		 * .
		 *
		 */
		virtual void EnableVirtualTerminalProcessing() override;

		/**
		 *
		 * .
		 *
		 */
		virtual void ResetTerminalFormat() override;

		/**
		 *
		 * .
		 *
		 * @param foreground
		 * @param background
		 * @param styles
		 */
		virtual void SetVirtualTerminalFormat(FakeConsoleForeground foreground, FakeConsoleBackground background, std::set<FakeConsoleTextStyle> styles) override;

		/**
		 *
		 * .
		 *
		 */
		virtual void Clear() override;

		/**
		 *
		 * .
		 *
		 * @param foreground
		 * @param background
		 * @param styles
		 */
		virtual void Write(const FakeString &str, FakeConsoleForeground foreground = FakeConsoleForeground::NONE, FakeConsoleBackground background = FakeConsoleBackground::NONE, std::set<FakeConsoleTextStyle> styles = {}) override;

		/**
		 *
		 * .
		 *
		 * @param foreground
		 * @param background
		 * @param styles
		 */
		virtual void WriteLine(const FakeString &str, FakeConsoleForeground foreground = FakeConsoleForeground::NONE, FakeConsoleBackground background = FakeConsoleBackground::NONE, std::set<FakeConsoleTextStyle> styles = {}) override;

		/**
		 *
		 * .
		 *
		 */
		virtual void WriteLine() override;
	};
