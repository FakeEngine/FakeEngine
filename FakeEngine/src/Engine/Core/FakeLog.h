/*****************************************************************
 * \file   FakeLog.h
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

#include <stdarg.h>
#include "Engine/Core/Window/FakeConsole.h"

enum class FakeLogLevel
	{
	None = 0,
	InfoLevel, TraceLevel, ErrorLevel, FatalLevel, WarningLevel
	};

/**
 * 
 * .
 * 
 */
class FAKE_API FakeLog
	{
	private:
		static FakeLogLevel Severity;
		static FakeRef<FakeConsole> Console;

	public:

		static void SetLogLevel(FakeLogLevel level)
			{
			Severity = level;
			}

		/**
		 *
		 * The actual Print function, that receives the values from the predefined macros and print the values in the right format and LogLevel into the console.
		 *
		 * @param format The Format String, which still contains the placeholder values instead and it is going to be modified inside of this function.
		 * @param ... The actual replace values in form of a list. They can be used to replace the placeholder Strings inside the format parameter.
		 */
		static void Print(const char *format, ...);
	};

#define FAKE_LOG(format, ...) { FakeLog::SetLogLevel(FakeLogLevel::None); FakeLog::Print(format, __VA_ARGS__); }
#define FAKE_LOG_TRACE(format, ...) { FakeLog::SetLogLevel(FakeLogLevel::TraceLevel); FakeLog::Print(format, __VA_ARGS__); }
#define FAKE_LOG_INFO(format, ...) { FakeLog::SetLogLevel(FakeLogLevel::InfoLevel); FakeLog::Print(format, __VA_ARGS__); }
#define FAKE_LOG_ERROR(format, ...) { FakeLog::SetLogLevel(FakeLogLevel::ErrorLevel); FakeLog::Print(format, __VA_ARGS__); }
#define FAKE_LOG_FATAL(format, ...) { FakeLog::SetLogLevel(FakeLogLevel::FatalLevel); FakeLog::Print(format, __VA_ARGS__); }
#define FAKE_LOG_WARN(format, ...) { FakeLog::SetLogLevel(FakeLogLevel::WarningLevel); FakeLog::Print(format, __VA_ARGS__); }

