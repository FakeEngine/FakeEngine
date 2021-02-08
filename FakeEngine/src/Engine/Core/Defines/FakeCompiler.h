/*****************************************************************
 * \file   FakeCompiler.h
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


#ifdef _MSC_VER

#if _MSC_VER < 1900
#error "Required Visual Studio 2015 or newer."
#endif

#define FAKE_DLL_EXPORT __declspec(dllexport)
#define FAKE_DLL_IMPORT __declspec(dllimport)
#define FAKE_INLINE __inline
#define FAKE_FORCE_INLINE __forceinline
#define FAKE_FORCE_NOINLINE __declspec(noinline)
#define FAKE_STDCALL __stdcall
#define FAKE_THREADLOCAL __declspec(thread)
#define FAKE_NORETURN __declspec(noreturn)
#define FAKE_PACK_BEGIN() __pragma(pack(push, 1))
#define FAKE_PACK_END() ; __pragma(pack(pop))
#define FAKE_ALIGN_BEGIN(_align) __declspec(align(_align))
#define FAKE_ALIGN_END(_align) /* NOTHING */
#define FAKE_OFFSET_OF(X, Y) offsetof(X, Y)
#define FAKE_DEPRECATED __declspec(deprecated)

#pragma warning(disable: 4251)

#elif defined(__clang__)

#define FAKE_DLL_EXPORT __attribute__ ((_visibility_ ("default")))
#define FAKE_DLL_IMPORT /* NOTHING */
#define FAKE_INLINE inline
#define FAKE_FORCE_INLINE inline
#define FAKE_FORCE_NOINLINE __attribute__ ((noinline))
#define FAKE_STDCALL __attribute__ ((stdcall))
#define FAKE_THREADLOCAL __thread
#define FAKE_NORETURN __attribute__ ((noreturn))
#define FAKE_PACK_BEGIN() /* NOTHING */
#define FAKE_PACK_END() __attribute__ ((__packed__))
#define FAKE_ALIGN_BEGIN(_align) /* NOTHING */
#define FAKE_ALIGN_END(_align) __attribute__ ((aligned(_align)))
#define FAKE_OFFSET_OF(X, Y) __builtin_offsetof(X, Y)
#define FAKE_DEPRECATED /* NOTHING */

#pragma clang diagnostic ignored "-Wswitch"
#pragma clang diagnostic ignored "-Wmacro-redefined"
#pragma clang diagnostic ignored "-Waddress-of-packed-member"
#pragma clang diagnostic ignored "-Wnull-dereference"
#pragma clang diagnostic ignored "-Winvalid-noreturn"

#elif defined(__GNUC__)

#define FAKE_DLL_EXPORT __declspec(dllexport)
#define FAKE_DLL_IMPORT /* NOTHING */
#define FAKE_INLINE inline
#define FAKE_FORCE_INLINE inline
#define FAKE_FORCE_NOINLINE __attribute__((noinline))
#define FAKE_STDCALL __attribute__((stdcall))
#define FAKE_THREADLOCAL __thread
#define FAKE_NORETURN __attribute__((noreturn))
#define FAKE_PACK_BEGIN() /* NOTHING */
#define FAKE_PACK_END() __attribute__((__packed__))
#define FAKE_ALIGN_BEGIN(_align) /* NOTHING */
#define FAKE_ALIGN_END(_align) __attribute__((aligned(_align)))
#define FAKE_OFFSET_OF(X, Y) __builtin_offsetof(X, Y)
#define FAKE_DEPRECATED __attribute__((deprecated))

#elif defined(__INTEL_COMPILER)

#define FAKE_DLL_EXPORT ??
#define FAKE_DLL_IMPORT ??
#define FAKE_INLINE inline
#define FAKE_FORCE_INLINE inline
#define FAKE_FORCE_NOINLINE /* NOTHING */
#define FAKE_STDCALL __stdcall
#define FAKE_NORETURN ??
#define FAKE_PACK_BEGIN() ??
#define FAKE_PACK_END() ??
#define FAKE_ALIGN_BEGIN(_align) ??
#define FAKE_ALIGN_END(_align) ??
#define FAKE_OFFSET_OF(X, Y) ??
#define FAKE_DEPRECATED ??

#ifdef _WIN32
#define FAKE_THREADLOCAL __declspec(thread)
#else
#define FAKE_THREADLOCAL __thread
#endif

#else

#pragma error "Unknown Compiler"

#endif

#define FAKE_PACK_STRUCT(__declaration__) FAKE_PACK_BEGIN() __declaration__ FAKE_PACK_END()

