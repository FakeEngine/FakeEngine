#include "FakePch.h"
#include "FakeTextureCube.h"

#include "Engine/Platform/OpenGL/FakeOpenGLTextureCube.h"

FakeRef<FakeTextureCube> FakeTextureCube::Create(const FakeString &path)
    {
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLTextureCube>::Create(path);
	#endif
    }

FakeRef<FakeTextureCube> FakeTextureCube::Create(FakeTextureFormat format, uint32 width, uint32 height)
    {
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLTextureCube>::Create(format, width, height);
	#endif
    }

