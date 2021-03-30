#include "FakePch.h"
#include "FakeRenderer2D.h"

#include "FakeRenderer.h"
#include "FakeShader.h"
#include "FakeVertexBuffer.h"
#include "FakeIndexBuffer.h"
#include "FakePipeline.h"

struct QuadVertex
	{
	FakeVec3f Position;
	FakeVec4f Color;
	FakeVec2f TexCoord;
	float TexIndex;
	float TilingFactor;
	};

struct LineVertex
	{
	FakeVec3f Position;
	FakeVec4f Color;
	};

struct CircleVertex
	{
	FakeVec3f WorldPosition;
	FakeVec2f LocalPosition;
	FakeVec4f Color;
	float Thickness;
	};

struct FakeRenderer2DData
	{
	static const uint32 MaxQuads = 20000;
	static const uint32 MaxVertices = MaxQuads * 4;
	static const uint32 MaxIndices = MaxQuads * 6;
	static const uint32 MaxTextureSlots = 32;

	static const uint32 MaxLines = 10000;
	static const uint32 MaxLineVertices = MaxLines * 2;
	static const uint32 MaxLineIndices = MaxLines * 6;

	FakeRef<FakePipeline> QuadPipeline;
	FakeRef<FakePipeline> CirclePipeline;
	FakeRef<FakePipeline> LinePipeline;

	FakeRef<FakeTexture2D> WhiteTexture;
	FakeVec4f QuadVertexPositions[4];

	FakeRef<FakeShader> TextureShader;
	FakeRef<FakeShader> CircleShader;
	FakeRef<FakeShader> LineShader;

	uint32 QuadIndexCount = 0;
	QuadVertex *QuadVertexBufferBase = nullptr;
	QuadVertex *QuadVertexBufferPtr = nullptr;

	uint32 CircleIndexCount = 0;
	CircleVertex *CircleVertexBufferBase = nullptr;
	CircleVertex *CircleVertexBufferPtr = nullptr;

	uint32 LineIndexCount = 0;
	LineVertex *LineVertexBufferBase = nullptr;
	LineVertex *LineVertexBufferPtr = nullptr;

	std::array<FakeRef<FakeTexture2D>, MaxTextureSlots> TextureSlots;
	uint32 TextureSlotIndex = 1; // 0 = White Texture

	FakeMat4f CameraViewProjection;
	bool DepthTest = true;
	FakeRenderer2D::Statistics Stats;
	};

static FakeRenderer2DData *Data;

void FakeRenderer2D::FlushAndReset()
	{
	EndScene();

	Data->QuadIndexCount = 0;
	Data->QuadVertexBufferPtr = Data->QuadVertexBufferBase;
	Data->TextureSlotIndex = 1;
	}

void FakeRenderer2D::FlushAndResetLines()
	{
	}

void FakeRenderer2D::Init()
    {
	Data = new FakeRenderer2DData;

	// SHADERS
	Data->TextureShader = FakeRenderer::GetShaderLibrary().Get("FakeTextureShader");
	Data->LineShader = nullptr;
	Data->CircleShader = nullptr;

	// QUADS
	FakePipelineSpecification quadVertexBufferPipeline;
	quadVertexBufferPipeline.Layout = {
		{ FakeShaderDataType::Float3, "a_Position" },
		{ FakeShaderDataType::Float4, "a_Color" },
		{ FakeShaderDataType::Float2, "a_TexCoord" },
		{ FakeShaderDataType::Float, "a_TexIndex" },
		{ FakeShaderDataType::Float, "a_TilingFactor" }
	};

	Data->QuadVertexBufferBase = new QuadVertex[Data->MaxVertices];
	quadVertexBufferPipeline.VertexBuffer = FakeVertexBuffer::Create(Data->MaxVertices * sizeof(QuadVertex));

	uint32 *quadIndices = new uint32[Data->MaxIndices];
	uint32 offset = 0;
	for (uint32 i = 0; i < Data->MaxIndices; i += 6)
		{
		quadIndices[i + 0] = offset + 0;
		quadIndices[i + 1] = offset + 1;
		quadIndices[i + 2] = offset + 2;

		quadIndices[i + 3] = offset + 2;
		quadIndices[i + 4] = offset + 3;
		quadIndices[i + 5] = offset + 0;

		offset += 4;
		}

	quadVertexBufferPipeline.IndexBuffer = FakeIndexBuffer::Create(quadIndices, Data->MaxIndices);
	delete[] quadIndices;
	Data->QuadPipeline = FakePipeline::Create(quadVertexBufferPipeline);

	// TEXTURE
	Data->WhiteTexture = FakeTexture2D::Create(FakeTextureFormat::RGBA, 1, 1);
	uint32 whiteTextureData = 0xffffffff;
	Data->WhiteTexture->Lock();
	Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32));
	Data->WhiteTexture->Unlock();

	Data->TextureSlots[0] = Data->WhiteTexture;
	Data->QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	Data->QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
	Data->QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
	Data->QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

	// LINES
	FakePipelineSpecification lineVertexBufferPipeline;
	lineVertexBufferPipeline.Layout = {
		{ FakeShaderDataType::Float3, "a_Position" },
		{ FakeShaderDataType::Float4, "a_Color" }
	};

	Data->LineVertexBufferBase = new LineVertex[Data->MaxLineVertices];
	lineVertexBufferPipeline.VertexBuffer = FakeVertexBuffer::Create(Data->MaxLineVertices * sizeof(LineVertex));

	uint32 *lineIndices = new uint32[Data->MaxLineIndices];
	for (uint32 i = 0; i < Data->MaxLineIndices; ++i)
		lineIndices[i] = i;

	lineVertexBufferPipeline.IndexBuffer = FakeIndexBuffer::Create(lineIndices, Data->MaxLineIndices);
	delete[] lineIndices;
	Data->LinePipeline = FakePipeline::Create(lineVertexBufferPipeline);

	// CIRCLES
	FakePipelineSpecification circleVertexBufferPipeline;
	circleVertexBufferPipeline.Layout = {
		{ FakeShaderDataType::Float3, "a_WorldPosition" },
		{ FakeShaderDataType::Float, "a_Thickness" },
		{ FakeShaderDataType::Float2, "a_LocalPosition" },
		{ FakeShaderDataType::Float4, "a_Color" },
	};

	Data->CircleVertexBufferBase = new CircleVertex[Data->MaxVertices];
	circleVertexBufferPipeline.VertexBuffer = FakeVertexBuffer::Create(Data->MaxVertices * sizeof(CircleVertex));
	Data->CirclePipeline = FakePipeline::Create(circleVertexBufferPipeline);
    }

void FakeRenderer2D::Shutdown()
    {
	delete Data;
    }

void FakeRenderer2D::BeginScene(const FakeMat4f &viewProjection, bool depthTest)
	{
	Data->CameraViewProjection = viewProjection;
	Data->DepthTest = depthTest;

	Data->TextureShader->Bind();
	Data->TextureShader->SetUniform("u_ViewProjection", Data->CameraViewProjection);

	Data->QuadIndexCount = 0;
	Data->QuadVertexBufferPtr = Data->QuadVertexBufferBase;

	Data->LineIndexCount = 0;
	Data->LineVertexBufferPtr = Data->LineVertexBufferBase;

	Data->CircleIndexCount = 0;
	Data->CircleVertexBufferPtr = Data->CircleVertexBufferBase;

	Data->TextureSlotIndex = 1;
	}

void FakeRenderer2D::EndScene()
	{
	uint32 dataSize = (uint8*)Data->QuadVertexBufferPtr - (uint8*)Data->QuadVertexBufferBase;
	if (dataSize)
		{
		Data->QuadPipeline->GetSpecification().VertexBuffer->SetData(Data->QuadVertexBufferBase, dataSize);

		Data->TextureShader->Bind();
		Data->TextureShader->SetUniform("u_ViewProjection", Data->CameraViewProjection);

		for (uint32 i = 0; i < Data->TextureSlotIndex; ++i)
			Data->TextureSlots[i]->Bind(i);

		Data->QuadPipeline->GetSpecification().VertexBuffer->Bind();
		Data->QuadPipeline->Bind();
		Data->QuadPipeline->GetSpecification().IndexBuffer->Bind();
		FakeRenderer::DrawIndexed(Data->QuadIndexCount, FakePrimitiveType::Triangles, Data->DepthTest);
		Data->Stats.DrawCalls++;
		}

	dataSize = (uint8*)Data->LineVertexBufferPtr - (uint8*)Data->LineVertexBufferBase;
	if (dataSize)
		{
		Data->LinePipeline->GetSpecification().VertexBuffer->SetData(Data->LineVertexBufferBase, dataSize);

		Data->LineShader->Bind();
		Data->LineShader->SetUniform("u_ViewProjection", Data->CameraViewProjection);

		Data->LinePipeline->GetSpecification().VertexBuffer->Bind();
		Data->LinePipeline->Bind();
		Data->LinePipeline->GetSpecification().IndexBuffer->Bind();
		FakeRenderer::SetLineThickness(2.0f);
		FakeRenderer::DrawIndexed(Data->LineIndexCount, FakePrimitiveType::Lines, false);
		Data->Stats.DrawCalls++;
		}

	dataSize = (uint8*)Data->CircleVertexBufferPtr - (uint8*)Data->CircleVertexBufferBase;
	if (dataSize)
		{
		Data->CirclePipeline->GetSpecification().VertexBuffer->SetData(Data->CircleVertexBufferBase, dataSize);

		Data->CircleShader->Bind();
		Data->CircleShader->SetUniform("u_ViewProjection", Data->CameraViewProjection);

		Data->CirclePipeline->GetSpecification().VertexBuffer->Bind();
		Data->CirclePipeline->Bind();
		Data->CirclePipeline->GetSpecification().IndexBuffer->Bind();
		FakeRenderer::DrawIndexed(Data->CircleIndexCount, FakePrimitiveType::Triangles, false);
		Data->Stats.DrawCalls++;
		}
	}

void FakeRenderer2D::Flush()
	{
	}

void FakeRenderer2D::ResetStats()
	{
	memset(&Data->Stats, 0, sizeof(Statistics));
	}

FakeRenderer2D::Statistics FakeRenderer2D::GetStats()
	{
	return Data->Stats;
	}

void FakeRenderer2D::DrawQuad(const FakeMat4f &transform, const FakeVec4f &color)
	{
	constexpr size_t quadVertexCount = 4;
	FakeVec2f textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
	const float textureIndex = 0.0f;
	const float tilingFactor = 1.0f;

	if (Data->QuadIndexCount >= FakeRenderer2DData::MaxIndices)
		FlushAndReset();

	for (size_t i = 0; i < quadVertexCount; ++i)
		{
		Data->QuadVertexBufferPtr->Position = transform * Data->QuadVertexPositions[i];
		Data->QuadVertexBufferPtr->Color = color;
		Data->QuadVertexBufferPtr->TexCoord = textureCoords[i];
		Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data->QuadVertexBufferPtr++;
		}

	Data->QuadIndexCount += 6;
	Data->Stats.QuadCount++;
	}

void FakeRenderer2D::DrawQuad(const FakeVec2f &position, const FakeVec2f &size, const FakeVec4f &color)
	{
	DrawQuad({ position.X, position.Y, 0.0f }, size, color);
	}

void FakeRenderer2D::DrawQuad(const FakeVec3f &position, const FakeVec2f &size, const FakeVec4f &color)
	{
	if (Data->QuadIndexCount >= FakeRenderer2DData::MaxIndices)
		FlushAndReset();

	constexpr size_t quadVertexCount = 4;
	FakeVec2f textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
	const float textureIndex = 0.0f;
	const float tilingFactor = 1.0f;

//	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), { 0, 0, 1 }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	FakeMat4f transform = FakeMat4f(1.0f);

	for (size_t i = 0; i < quadVertexCount; ++i)
		{
		Data->QuadVertexBufferPtr->Position = transform * Data->QuadVertexPositions[i];
		Data->QuadVertexBufferPtr->Color = color;
		Data->QuadVertexBufferPtr->TexCoord = textureCoords[i];
		Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
		Data->QuadVertexBufferPtr++;
		}

	Data->QuadIndexCount += 6;
	Data->Stats.QuadCount++;
	}

void FakeRenderer2D::DrawTexture(const FakeMat4f &transform, const FakeRef<FakeTexture2D> &texture, float tilingFactor, const FakeVec4f &tintColor)
	{
	if (Data->QuadIndexCount >= FakeRenderer2DData::MaxIndices)
		FlushAndReset();

	FakeVec4f color = { 1.0f, 1.0f, 1.0f, 1.0f };

	float textureIndex = 0.0f;
	for (uint32_t i = 1; i < Data->TextureSlotIndex; i++)
		{
		if (*Data->TextureSlots[i].Raw() == *texture.Raw())
			{
			textureIndex = (float) i;
			break;
			}
		}

	if (textureIndex == 0.0f)
		{
		textureIndex = (float)Data->TextureSlotIndex;
		Data->TextureSlots[Data->TextureSlotIndex] = texture;
		Data->TextureSlotIndex++;
		}

	Data->QuadVertexBufferPtr->Position = transform * Data->QuadVertexPositions[0];
	Data->QuadVertexBufferPtr->Color = color;
	Data->QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
	Data->QuadVertexBufferPtr->TexIndex = textureIndex;
	Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	Data->QuadVertexBufferPtr++;

	Data->QuadVertexBufferPtr->Position = transform * Data->QuadVertexPositions[1];
	Data->QuadVertexBufferPtr->Color = color;
	Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
	Data->QuadVertexBufferPtr->TexIndex = textureIndex;
	Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	Data->QuadVertexBufferPtr++;

	Data->QuadVertexBufferPtr->Position = transform * Data->QuadVertexPositions[2];
	Data->QuadVertexBufferPtr->Color = color;
	Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
	Data->QuadVertexBufferPtr->TexIndex = textureIndex;
	Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	Data->QuadVertexBufferPtr++;

	Data->QuadVertexBufferPtr->Position = transform * Data->QuadVertexPositions[3];
	Data->QuadVertexBufferPtr->Color = color;
	Data->QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
	Data->QuadVertexBufferPtr->TexIndex = textureIndex;
	Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	Data->QuadVertexBufferPtr++;

	Data->QuadIndexCount += 6;
	Data->Stats.QuadCount++;
	}

void FakeRenderer2D::DrawTexture(const FakeVec2f &position, const FakeVec2f &size, const FakeRef<FakeTexture2D> &texture, float tilingFactor, const FakeVec4f &tintColor)
	{
	DrawTexture({ position.X, position.Y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

void FakeRenderer2D::DrawTexture(const FakeVec3f &position, const FakeVec2f &size, const FakeRef<FakeTexture2D> &texture, float tilingFactor, const FakeVec4f &tintColor)
	{
	if (Data->QuadIndexCount >= FakeRenderer2DData::MaxIndices)
		FlushAndReset();

	FakeVec4f color = { 1.0f, 1.0f, 1.0f, 1.0f };

	float textureIndex = 0.0f;
	for (uint32_t i = 1; i < Data->TextureSlotIndex; i++)
		{
		if (*Data->TextureSlots[i].Raw() == *texture.Raw())
			{
			textureIndex = (float) i;
			break;
			}
		}

	if (textureIndex == 0.0f)
		{
		textureIndex = (float) Data->TextureSlotIndex;
		Data->TextureSlots[Data->TextureSlotIndex] = texture;
		Data->TextureSlotIndex++;
		}

	// glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), { 0, 0, 1 }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	FakeMat4f transform = FakeMat4f(1.0f);

	Data->QuadVertexBufferPtr->Position = transform * Data->QuadVertexPositions[0];
	Data->QuadVertexBufferPtr->Color = color;
	Data->QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
	Data->QuadVertexBufferPtr->TexIndex = textureIndex;
	Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	Data->QuadVertexBufferPtr++;

	Data->QuadVertexBufferPtr->Position = transform * Data->QuadVertexPositions[1];
	Data->QuadVertexBufferPtr->Color = color;
	Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
	Data->QuadVertexBufferPtr->TexIndex = textureIndex;
	Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	Data->QuadVertexBufferPtr++;

	Data->QuadVertexBufferPtr->Position = transform * Data->QuadVertexPositions[2];
	Data->QuadVertexBufferPtr->Color = color;
	Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
	Data->QuadVertexBufferPtr->TexIndex = textureIndex;
	Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	Data->QuadVertexBufferPtr++;

	Data->QuadVertexBufferPtr->Position = transform * Data->QuadVertexPositions[3];
	Data->QuadVertexBufferPtr->Color = color;
	Data->QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
	Data->QuadVertexBufferPtr->TexIndex = textureIndex;
	Data->QuadVertexBufferPtr->TilingFactor = tilingFactor;
	Data->QuadVertexBufferPtr++;

	Data->QuadIndexCount += 6;
	Data->Stats.QuadCount++;
	}

