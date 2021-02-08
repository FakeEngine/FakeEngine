#include "FakePch.h"
#include "FakeIndexBuffer.h"

#include "Engine/Platform/OpenGL/FakeOpenGLIndexBuffer.h"

FakeRef<FakeIndexBuffer> FakeIndexBuffer::Create(void *data, uint32 size)
	{
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLIndexBuffer>::Create(data, size);
	#endif
	}

FakeRef<FakeIndexBuffer> FakeIndexBuffer::Create(uint32 size)
	{
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLIndexBuffer>::Create(size);
	#endif
	}

