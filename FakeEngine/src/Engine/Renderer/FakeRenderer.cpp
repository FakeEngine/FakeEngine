#include "FakePch.h"
#include "FakeRenderer.h"

#include "FakeShader.h"
#include "FakeRenderer2D.h"

FakeRendererAPIType FakeRendererAPI::CurrentRendererAPI = FakeRendererAPIType::OpenGL;

struct FakeRendererData
	{
	FakeRef<FakeRenderPass> ActiveRenderPass;
	FakeRef<FakeShaderLibrary> ShaderLibrary;
	FakeRenderCommandQueue CommandQueue;
	};

static FakeRendererData Data;

FakeRenderCommandQueue &FakeRenderer::GetRenderCommandQueue()
	{
	return Data.CommandQueue;
	}

void FakeRenderer::Init()
	{
	Data.ShaderLibrary = FakeRef<FakeShaderLibrary>::Create();
	FakeRenderer::Submit([]() { FakeRendererAPI::Init(); });

	Data.ShaderLibrary->Load("assets/shaders/FakeFlatColorShader.glsl");
	Data.ShaderLibrary->Load("assets/shaders/FakeTextureShader.glsl");
	Data.ShaderLibrary->Load("assets/shaders/FakeSimpleTextureShader.glsl");

	FakeRenderer2D::Init();
	}

void FakeRenderer::Shutdown()
	{
	FakeRenderer2D::Shutdown();
	

	}

void FakeRenderer::Clear()
	{
	FakeRenderer::Submit([]() { FakeRendererAPI::Clear(); });
	}

void FakeRenderer::SetClearColor(float r, float g, float b, float a)
	{
	FakeRenderer::Submit([=]() { FakeRendererAPI::SetClearColor(r, g, b, a); });
	}

void FakeRenderer::SetClearColor(const FakeVec4f &color)
	{
	FakeRenderer::Submit([=]() { FakeRendererAPI::SetClearColor(color); });
	}

void FakeRenderer::SetLineThickness(float thickness)
	{
	FakeRenderer::Submit([=]() { FakeRendererAPI::SetLineThickness(thickness); });
	}

void FakeRenderer::DrawIndexed(uint32 count, FakePrimitiveType type, bool depthTest)
	{
	FakeRenderer::Submit([=]() { FakeRendererAPI::DrawIndexed(count, type, depthTest); });
	}

void FakeRenderer::SetViewport(uint32 width, uint32 height)
	{
	FakeRenderer::Submit([=]() { FakeRendererAPI::SetViewport(width, height); });
	}

void FakeRenderer::Render()
	{
	Data.CommandQueue.Execute();
	}

void FakeRenderer::BeginRenderPass(FakeRef<FakeRenderPass> renderPass, bool shouldClear)
	{
	FAKE_ASSERT(renderPass, "RenderPass can not be null!");

	Data.ActiveRenderPass = renderPass;
	renderPass->GetSpecification().TargetFramebuffer->Bind();
	if (shouldClear)
		{
		const FakeVec4f &clearColor = renderPass->GetSpecification().TargetFramebuffer->GetSpecification().ClearColor;
		FakeRenderer::Submit([=]()
			{
			FakeRendererAPI::SetClearColor(clearColor);
			FakeRendererAPI::Clear();
			});
		}
	}

void FakeRenderer::EndRenderPass()
	{
	FAKE_ASSERT(Data.ActiveRenderPass, "No Active Render Pass!");
	Data.ActiveRenderPass->GetSpecification().TargetFramebuffer->Unbind();
	Data.ActiveRenderPass = nullptr;
	}

FakeShaderLibrary &FakeRenderer::GetShaderLibrary()
	{
	return *Data.ShaderLibrary;
	}
