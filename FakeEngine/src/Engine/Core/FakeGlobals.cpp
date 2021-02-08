#include "FakePch.h"
#include "FakeGlobals.h"

// Main engine directory folder
FakeString FakeGlobals::StartupFolder;

// temporary objects can be stored in this folder (everything will be deleted when the engine shuts down)
FakeString FakeGlobals::TemporaryFolder;

// directory which contains the project
FakeString FakeGlobals::ProjectFolder;

// the directory where the game executable files will be stored.
FakeString FakeGlobals::BinariesFolder;

// The product local data directory.
FakeString FakeGlobals::ProductLocalFolder;

#ifdef FAKE_USE_EDITOR

// Project specific cache folder path (editor-only).
FakeString FakeGlobals::ProjectCacheFolder;

// Engine content directory path (editor-only).
FakeString FakeGlobals::EngineContentFolder;

// Game source code directory path (editor-only).
FakeString FakeGlobals::ProjectSourceFolder;

#endif

// Project content directory path
FakeString FakeGlobals::ProjectContentFolder;

// Mono library folder path
FakeString FakeGlobals::MonoPath;

// State

// True if a fatal error occurred (engine will be shut down).
bool FakeGlobals::FatalErrorOccurred;

// True if engine should close in the next cycle.
bool FakeGlobals::IsRequestingExit;

// The exit code.
int32 FakeGlobals::ExitCode;

// Threading

// Main Engine Thread ID
uint64 FakeGlobals::MainThreadID;

// Config

// The full Engine verison
FakeString FakeGlobals::EngineVersion = FAKE_ENGINE_VERSION;

// The engine build version
int32 FakeGlobals::EngineBuildNumber = FAKE_ENGINE_BUILD;

// A short name of the product (can be "Fake Editor" or the name of the game e.g. MyAwesomeGame).
FakeString FakeGlobals::ProductName;

// The Company Name used for the app data directory on windows
FakeString FakeGlobals::CompanyName;

// The content data keyCode
int32 FakeGlobals::ContentKey;

// True if convert all loaded material by force
bool FakeGlobals::ForceConvertLoadedMaterials;