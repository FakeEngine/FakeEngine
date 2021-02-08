#include "FakePch.h"
#include "FakeTexture2D.h"

#include "Engine/Platform/OpenGL/FakeOpenGLTexture2D.h"

FakeRef<FakeTexture2D> FakeTexture2D::Create(const FakeString &path, bool srgb, FakeTextureWrap wrap)
    {
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLTexture2D>::Create(path, srgb, wrap);
	#endif
    }

FakeRef<FakeTexture2D> FakeTexture2D::Create(FakeTextureFormat format, uint32 width, uint32 height, FakeTextureWrap wrap)
    {
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLTexture2D>::Create(format, width, height, wrap);
	#endif
    }

