#include "FakePch.h"
#include "FakeFramebuffer.h"

#include "Engine/Platform/OpenGL/FakeOpenGLFramebuffer.h"

FakeRef<FakeFramebuffer> FakeFramebuffer::Create(const FakeFramebufferSpecification &spec)
	{
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLFramebuffer>::Create(spec);
	#endif
	}
