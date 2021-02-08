#include "FakePch.h"
#include "FakeOpenGLPipeline.h"

#include "Engine/Renderer/FakeRenderer.h"

namespace Utils
	{
	static GLenum fake_shader_data_type_to_open_gl_base_type(FakeShaderDataType type)
		{
		switch (type)
			{
			case FakeShaderDataType::Float:    return GL_FLOAT;
			case FakeShaderDataType::Float2:   return GL_FLOAT;
			case FakeShaderDataType::Float3:   return GL_FLOAT;
			case FakeShaderDataType::Float4:   return GL_FLOAT;
			case FakeShaderDataType::Mat2:     return GL_FLOAT;
			case FakeShaderDataType::Mat3:     return GL_FLOAT;
			case FakeShaderDataType::Mat4:     return GL_FLOAT;
			case FakeShaderDataType::Int:      return GL_INT;
			case FakeShaderDataType::Int2:     return GL_INT;
			case FakeShaderDataType::Int3:     return GL_INT;
			case FakeShaderDataType::Int4:     return GL_INT;
			case FakeShaderDataType::Bool:     return GL_BOOL;
			}

		FAKE_ASSERT(false);
		return 0;
		}
	}

FakeOpenGLPipeline::FakeOpenGLPipeline(const FakePipelineSpecification &spec)
	: Specification(spec)
	{
	Invalidate();
	}

FakeOpenGLPipeline::~FakeOpenGLPipeline()
	{
	GLuint rendererID = RendererID;
	FakeRenderer::Submit([rendererID]()
		{
		glDeleteVertexArrays(1, &rendererID);
		});
	}

void FakeOpenGLPipeline::Bind() const
	{
	FakeRef<const FakeOpenGLPipeline> instance = this;
	FakeRenderer::Submit([instance]()
		{
		glBindVertexArray(instance->RendererID);

		const auto &layout = instance->Specification.Layout;
		uint32 vertexAttribIndex = 0;
		for (const auto &element : layout)
			{
			auto glBaseType = Utils::fake_shader_data_type_to_open_gl_base_type(element.Type);
			glEnableVertexAttribArray(vertexAttribIndex);
			if (glBaseType == GL_INT)
				glVertexAttribIPointer(vertexAttribIndex, element.GetComponentCount(), glBaseType, layout.GetStride(), (const void*)(intptr_t)element.Offset);
			else
				glVertexAttribPointer(vertexAttribIndex, element.GetComponentCount(), glBaseType, element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)(intptr_t)element.Offset);

			++vertexAttribIndex;
			}
		});
	}

void FakeOpenGLPipeline::Unbind() const
	{
	GLuint rendererID = RendererID;
	FakeRenderer::Submit([rendererID]() { glBindVertexArray(rendererID); });
	}

FakeRendererID FakeOpenGLPipeline::GetRendererID() const
	{
	return RendererID;
	}

FakePipelineSpecification &FakeOpenGLPipeline::GetSpecification()
	{
	return Specification;
	}

const FakePipelineSpecification &FakeOpenGLPipeline::GetSpecification() const
	{
	return Specification;
	}

void FakeOpenGLPipeline::Invalidate()
	{
	FAKE_ASSERT(Specification.Layout.GetElements().size());

	FakeRef<FakeOpenGLPipeline> instance = this;
	FakeRenderer::Submit([instance]() mutable
		{
		auto &rendererID = instance->RendererID;

		if (rendererID)
			glDeleteVertexArrays(1, &rendererID);

		glGenVertexArrays(1, &rendererID);
		});
	}

