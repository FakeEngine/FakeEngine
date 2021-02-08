/*****************************************************************
 * \file   FakeAssert.h
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

#ifdef FAKE_DEBUG
#define FAKE_ENABLE_ASSERTS
#endif

#ifdef FAKE_ENABLE_ASSERTS
 // __VA_ARGS__ expansion to get past MSVC "bug"
#define FAKE_EXPAND_VARGS(x) x

#define FAKE_ASSERT_NO_MESSAGE(x) { if(!(x)) { FAKE_LOG_ERROR("Assertion Failed!"); __debugbreak(); } }
#define FAKE_ASSERT_MESSAGE(x, ...) { if(!(x)) { FAKE_LOG_ERROR("Assertion Failed: %s", __VA_ARGS__); __debugbreak(); } }

#define FAKE_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
#define FAKE_GET_ASSERT_MACRO(...) FAKE_EXPAND_VARGS(FAKE_ASSERT_RESOLVE(__VA_ARGS__, FAKE_ASSERT_MESSAGE, FAKE_ASSERT_NO_MESSAGE))

#define FAKE_ASSERT(...) FAKE_EXPAND_VARGS( FAKE_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
#define FAKE_ASSERT(...)
#endif
