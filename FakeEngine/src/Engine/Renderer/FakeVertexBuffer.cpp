#include "FakePch.h"
#include "FakeVertexBuffer.h"

#include "Engine/Platform/OpenGL/FakeOpenGLVertexBuffer.h"

FakeRef<FakeVertexBuffer> FakeVertexBuffer::Create(void *data, uint32 size, FakeVertexBufferUsage usage)
	{
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLVertexBuffer>::Create(data, size, usage);
	#endif
	}

FakeRef<FakeVertexBuffer> FakeVertexBuffer::Create(uint32 size, FakeVertexBufferUsage usage)
	{
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLVertexBuffer>::Create(size, usage);
	#endif
	}

