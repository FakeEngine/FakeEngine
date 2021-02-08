#include "FakePch.h"
#include "FakeOpenGLVertexBuffer.h"

#include "Engine/Renderer/FakeRenderer.h"

namespace Utils
	{
	static GLenum fake_open_gl_usage(FakeVertexBufferUsage usage)
		{
		switch (usage)
			{
			case FakeVertexBufferUsage::Static:    return GL_STATIC_DRAW;
			case FakeVertexBufferUsage::Dynamic:   return GL_DYNAMIC_DRAW;
			}

		FAKE_ASSERT(false);
		return 0;
		}
	}

FakeOpenGLVertexBuffer::FakeOpenGLVertexBuffer(void *data, uint32 size, FakeVertexBufferUsage usage)
	: Size(size), Usage(usage)
	{
	LocalData = FakeAllocator::Copy(data, size);
	
	FakeRef<FakeOpenGLVertexBuffer> instance = this;
	FakeRenderer::Submit([instance]() mutable
		{
		glCreateBuffers(1, &instance->RendererID);
		glNamedBufferData(instance->RendererID, instance->Size, instance->LocalData.Data, Utils::fake_open_gl_usage(instance->Usage));
		});
	}

FakeOpenGLVertexBuffer::FakeOpenGLVertexBuffer(uint32 size, FakeVertexBufferUsage usage)
	: Size(size), Usage(usage)
	{
	FakeRef<FakeOpenGLVertexBuffer> instance = this;
	FakeRenderer::Submit([instance]() mutable
		{
		glCreateBuffers(1, &instance->RendererID);
		glNamedBufferData(instance->RendererID, instance->Size, nullptr, Utils::fake_open_gl_usage(instance->Usage));
		});
	}

FakeOpenGLVertexBuffer::~FakeOpenGLVertexBuffer()
	{
	GLuint rendererID = RendererID;
	FakeRenderer::Submit([rendererID]() { glDeleteBuffers(1, &rendererID); });
	}

void FakeOpenGLVertexBuffer::SetData(void *data, uint32 size, uint32 offset)
	{
	LocalData = FakeAllocator::Copy(data, size);
	Size = size;

	FakeRef<FakeOpenGLVertexBuffer> instance = this;
	FakeRenderer::Submit([instance, offset]() { glNamedBufferSubData(instance->RendererID, offset, instance->LocalData.Size, instance->LocalData.Data); });
	}

void FakeOpenGLVertexBuffer::Bind() const
	{
	FakeRef<const FakeOpenGLVertexBuffer> instance = this;
	FakeRenderer::Submit([instance]() { glBindBuffer(GL_ARRAY_BUFFER, instance->RendererID); });
	}

void FakeOpenGLVertexBuffer::Unbind() const
	{
	FakeRenderer::Submit([]() { glBindBuffer(GL_ARRAY_BUFFER, 0); });
	}

