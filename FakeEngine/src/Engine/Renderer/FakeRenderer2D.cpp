#include "FakePch.h"
#include "FakeRenderer2D.h"

#include "FakeRenderer.h"
#include "FakeShader.h"
#include "FakeVertexBuffer.h"
#include "FakeIndexBuffer.h"
#include "FakePipeline.h"

struct FakeRenderer2DData
	{
	FakeRef<FakePipeline> QuadPipeline;
	FakeRef<FakeTexture2D> WhiteTexture;
	FakeMat4f ViewProjection;
	};

static FakeRenderer2DData *Data;

void FakeRenderer2D::Init()
    {
	Data = new FakeRenderer2DData;
	Data->WhiteTexture = FakeTexture2D::Create(FakeTextureFormat::RGBA, 1, 1, FakeTextureWrap::Clamp);
	uint32 whiteTextureData = 0xffffffff;
	Data->WhiteTexture->Lock();
	Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32));
	Data->WhiteTexture->Unlock();

	// CAMERA
	FakeMat4f translationMatrix = FakeMat4f::Translate({ 0.0f, 0.0f, 0.0f });
	FakeMat4f scaleMatrix = FakeMat4f::Scale({ 350.0f, 350.0f, 1.0f });
	FakeMat4f viewMatrix = FakeMat4f::Multiply(translationMatrix, scaleMatrix);
	Data->ViewProjection = FakeMat4f::Multiply(FakeMat4f::Ortho(1280.0f, 720.0f, -1.0f, 1.0f), viewMatrix);

	float squareVertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	uint32 squareIndices[] = { 0, 1, 2, 2, 3, 0 };

	FakePipelineSpecification spec;
	spec.VertexBuffer = FakeVertexBuffer::Create(squareVertices, sizeof(squareVertices));
	spec.IndexBuffer = FakeIndexBuffer::Create(squareIndices, sizeof(squareIndices));
	spec.Shader = FakeRenderer::GetShaderLibrary().Get("FakeSimpleTextureShader");
	spec.Layout = {
		{ FakeShaderDataType::Float3, "a_Position" },
		{ FakeShaderDataType::Float2, "a_TexCoord" }
	};

	Data->QuadPipeline = FakePipeline::Create(spec);
	Data->QuadPipeline->GetSpecification().Shader->Bind();
	Data->QuadPipeline->GetSpecification().Shader->SetUniform("u_Texture", 0);
    }

void FakeRenderer2D::Shutdown()
    {
	delete Data;
    }

void FakeRenderer2D::BeginScene()
	{
	Data->QuadPipeline->GetSpecification().Shader->Bind();
	Data->QuadPipeline->GetSpecification().Shader->SetUniform("u_ViewProjection", Data->ViewProjection);
	}

void FakeRenderer2D::EndScene()
	{
	}

void FakeRenderer2D::DrawQuad(const FakeVec3f &position, const FakeVec2f &size, float rotation, const FakeVec4f &color)
	{
	FakeMat4f transform = FakeMat4f::Translate(position) * FakeMat4f::Rotate(fake_radians(rotation), { 0, 0, 1 }) * FakeMat4f::Scale({ size.X, size.Y, 1.0f });

	Data->WhiteTexture->Bind();
	Data->QuadPipeline->GetSpecification().Shader->Bind();
	Data->QuadPipeline->GetSpecification().Shader->SetUniform("u_Color", color);
	Data->QuadPipeline->GetSpecification().Shader->SetUniform("u_TilingFactor", 1.0f);
	Data->QuadPipeline->GetSpecification().Shader->SetUniform("u_Transform", transform);

	Data->QuadPipeline->GetSpecification().VertexBuffer->Bind();
	Data->QuadPipeline->Bind();
	Data->QuadPipeline->GetSpecification().IndexBuffer->Bind();
	FakeRenderer::DrawIndexed(Data->QuadPipeline->GetSpecification().IndexBuffer->GetCount(), FakePrimitiveType::Triangles);
	}

void FakeRenderer2D::DrawTexture(const FakeVec3f &position, const FakeVec2f &size, float rotation, const FakeRef<FakeTexture2D> &texture, float tilingFactor, const FakeVec4f &tintColor)
	{
	FakeMat4f transform = FakeMat4f::Translate(position) * FakeMat4f::Rotate(fake_radians(rotation), { 0, 0, 1 }) * FakeMat4f::Scale({ size.X, size.Y, 1.0f });

	texture->Bind();
	Data->QuadPipeline->GetSpecification().Shader->Bind();
	Data->QuadPipeline->GetSpecification().Shader->SetUniform("u_Color", tintColor);
	Data->QuadPipeline->GetSpecification().Shader->SetUniform("u_TilingFactor", tilingFactor);
	Data->QuadPipeline->GetSpecification().Shader->SetUniform("u_Transform", transform);

	Data->QuadPipeline->GetSpecification().VertexBuffer->Bind();
	Data->QuadPipeline->Bind();
	Data->QuadPipeline->GetSpecification().IndexBuffer->Bind();
	FakeRenderer::DrawIndexed(Data->QuadPipeline->GetSpecification().IndexBuffer->GetCount(), FakePrimitiveType::Triangles);
	}
