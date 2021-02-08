#include "FakePch.h"
#include "FakeRenderPass.h"

#include "Engine/Platform/OpenGL/FakeOpenGLRenderPass.h"

FakeRef<FakeRenderPass> FakeRenderPass::Create(const FakeRenderPassSpecification &spec)
	{
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLRenderPass>::Create(spec);
	#endif
	}

