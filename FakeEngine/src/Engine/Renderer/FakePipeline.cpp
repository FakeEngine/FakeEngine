#include "FakePch.h"
#include "FakePipeline.h"

#include "Engine/Platform/OpenGL/FakeOpenGLPipeline.h"

FakeRef<FakePipeline> FakePipeline::Create(const FakePipelineSpecification &spec)
	{
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLPipeline>::Create(spec);
	#endif
	}

