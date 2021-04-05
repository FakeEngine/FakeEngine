/*****************************************************************
 * \file   FakeCore.h
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

#include "Engine/Core/DataTypes/FakeBaseTypes.h"
#include "Engine/Core/FakeReference.h"
#include "Engine/Core/FakeAssert.h"
#include "Engine/Core/FakeLog.h"
#include "Engine/Core/Profiler/FakeProfilerTimer.h"

#include "Engine/Core/Defines/FakeCompiler.h"
#include "Engine/Core/Defines/FakeConsole.h"
#include "Engine/Core/Defines/FakeMouseButtonCodes.h"
#include "Engine/Core/Defines/FakeKeyCodes.h"

#ifdef FAKE_BUILD_LIBRARY
	#ifdef FAKE_LIBRARY_EXPORT
		#define FAKE_API FAKE_DLL_EXPORT
	#else
		#define FAKE_API FAKE_DLL_IMPORT
	#endif
#else
	#define FAKE_API /* NOTHING */
#endif

#define FAKE_ENGINE_BUILD 154685
#define FAKE_ENGINE_VERSION "1.0.154685"

#define FAKE_MAX(A, B) ( ((A)  > (B)) ? (A) :  (B) )
#define FAKE_MIN(A, B) ( ((A)  < (B)) ? (A) :  (B) )
#define FAKE_ABS(A)	   ( ((A)  >= 0 ) ? (A) : -(A) )
#define FAKE_BIT(X)	   (1 << X)

#define FAKE_BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)
#define FAKE_OUT_OF_MEMORY FAKE_LOG_FATAL("Out of memory error!\nFile: %s\nLine: %d", __FILE__, __LINE__)

using FakeRendererID = uint32;

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
	{
	return std::make_unique<T>(std::forward<Args>(args)...);
	}

/**
 *
 * This struct contains the memory usage generated by using the keywords new and delete.
 *
 */
struct FakeAllocationMetrics
	{
	uint32 TotalAllocated = 0;	/**< The total amount of bytes allocated by the program. */
	uint32 TotalFreed = 0;		/**< The total amount of bytes freed by the program. */

	/**
	 *
	 * Returns the current memory usage in bytes.
	 *
	 * @return Returns the current memory usage in bytes.
	 */
	inline uint32 CurrentUsage() { return TotalAllocated - TotalFreed; }

	/**
	 *
	 * Returns the current memory usage in megabytes.
	 *
	 * @return Returns the current memory usage in megabytes
	 */
	inline uint32 CurrentUsageInMegaBytes() { return (TotalAllocated - TotalFreed) / 1000000; }
	};

void fake_print_current_memory_usage();

