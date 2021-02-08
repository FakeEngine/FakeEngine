#include "FakePch.h"
#include "FakeOpenGLIndexBuffer.h"

#include "Engine/Renderer/FakeRenderer.h"

FakeOpenGLIndexBuffer::FakeOpenGLIndexBuffer(void *data, uint32 size)
	: Size(size)
	{
	LocalData = FakeAllocator::Copy(data, size);

	FakeRef<FakeOpenGLIndexBuffer> instance = this;
	FakeRenderer::Submit([instance]() mutable
		{
		glCreateBuffers(1, &instance->RendererID);
		glNamedBufferData(instance->RendererID, instance->Size, instance->LocalData.Data, GL_STATIC_DRAW);
		});
	}

FakeOpenGLIndexBuffer::FakeOpenGLIndexBuffer(uint32 size)
	: Size(size)
	{
	FakeRef<FakeOpenGLIndexBuffer> instance = this;
	FakeRenderer::Submit([instance]() mutable
		{
		glCreateBuffers(1, &instance->RendererID);
		glNamedBufferData(instance->RendererID, instance->Size, nullptr, GL_DYNAMIC_DRAW);
		});
	}

FakeOpenGLIndexBuffer::~FakeOpenGLIndexBuffer()
	{
	GLuint rendererID = RendererID;
	FakeRenderer::Submit([rendererID]() { glDeleteBuffers(1, &rendererID); });
	}

void FakeOpenGLIndexBuffer::SetData(void *data, uint32 size, uint32 offset)
	{
	LocalData = FakeAllocator::Copy(data, size);
	Size = size;

	FakeRef<FakeOpenGLIndexBuffer> instance = this;
	FakeRenderer::Submit([instance, offset]()
		{
		glNamedBufferSubData(instance->RendererID, offset, instance->Size, instance->LocalData.Data);
		});
	}

void FakeOpenGLIndexBuffer::Bind() const
	{
	FakeRef<const FakeOpenGLIndexBuffer> instance = this;
	FakeRenderer::Submit([instance]() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, instance->RendererID); });
	}

void FakeOpenGLIndexBuffer::Unbind() const
	{
	FakeRenderer::Submit([]() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); });
	}

uint32 FakeOpenGLIndexBuffer::GetCount() const
	{
	return Size / sizeof(uint32);
	}

uint32 FakeOpenGLIndexBuffer::GetSize() const
	{
	return Size;
	}

FakeRendererID FakeOpenGLIndexBuffer::GetRendererID() const
	{
	return RendererID;
	}
