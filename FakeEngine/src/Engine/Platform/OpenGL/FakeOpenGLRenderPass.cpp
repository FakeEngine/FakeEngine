#include "FakePch.h"
#include "FakeOpenGLRenderPass.h"

FakeOpenGLRenderPass::FakeOpenGLRenderPass(const FakeRenderPassSpecification &spec)
	: Specification(spec)
	{
	}

FakeOpenGLRenderPass::~FakeOpenGLRenderPass()
	{
	}

FakeRenderPassSpecification &FakeOpenGLRenderPass::GetSpecification()
	{
	return Specification;
	}

const FakeRenderPassSpecification &FakeOpenGLRenderPass::GetSpecification() const
	{
	return Specification;
	}
