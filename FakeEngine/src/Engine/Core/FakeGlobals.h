/*****************************************************************
 * \file   FakeGlobals.h
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

/**
 * 
 * .
 * 
 */
class FAKE_API FakeGlobals
	{
	public:

		// Paths

		// Main engine directory folder
		static FakeString StartupFolder;

		// temporary objects can be stored in this folder (everything will be deleted when the engine shuts down)
		static FakeString TemporaryFolder;

		// directory which contains the project
		static FakeString ProjectFolder;

		// the directory where the game executable files will be stored.
		static FakeString BinariesFolder;

		// The product local data directory.
		static FakeString ProductLocalFolder;

#ifdef FAKE_USE_EDITOR

		// Project specific cache folder path (editor-only).
		static FakeString ProjectCacheFolder;

		// Engine content directory path (editor-only).
		static FakeString EngineContentFolder;

		// Game source code directory path (editor-only).
		static FakeString ProjectSourceFolder;

#endif

		// Project content directory path
		static FakeString ProjectContentFolder;

		// Mono library folder path
		static FakeString MonoPath;

		// State

		// True if a fatal error occurred (engine will be shut down).
		static bool FatalErrorOccurred;

		// True if engine should close in the next cycle.
		static bool IsRequestingExit;

		// The exit code.
		static int32 ExitCode;

		// Threading

		// Main Engine Thread ID
		static uint64 MainThreadID;

		// Config

		// The full Engine verison
		static FakeString EngineVersion;

		// The engine build version
		static int32 EngineBuildNumber;

		// A short name of the product (can be "Fake Editor" or the name of the game e.g. MyAwesomeGame).
		static FakeString ProductName;

		// The Company Name used for the app data directory on windows
		static FakeString CompanyName;

		// The content data keyCode
		static int32 ContentKey;

		// True if convert all loaded material by force
		static bool ForceConvertLoadedMaterials;
	};
