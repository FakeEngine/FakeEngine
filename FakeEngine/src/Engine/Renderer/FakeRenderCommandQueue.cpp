#include "FakePch.h"
#include "FakeRenderCommandQueue.h"

FakeRenderCommandQueue::FakeRenderCommandQueue()
	{
	CommandBuffer = new uint8[10 * 1024 * 1024]; // 10mb Buffer
	CommandBufferPtr = CommandBuffer;
	memset(CommandBuffer, 0, 10 * 1024 * 1024);
	}

FakeRenderCommandQueue::~FakeRenderCommandQueue()
	{
	delete[] CommandBuffer;
	}

void *FakeRenderCommandQueue::Allocate(FakeRenderCommandFn func, uint32 size)
	{
	*(FakeRenderCommandFn*)CommandBufferPtr = func;
	CommandBufferPtr += sizeof(FakeRenderCommandFn);

	*(uint32*)CommandBufferPtr = size;
	CommandBufferPtr += sizeof(uint32);

	void *memory = CommandBufferPtr;
	CommandBufferPtr += size;

	CommandCount++;
	return memory;
	}

void FakeRenderCommandQueue::Execute()
	{
	Byte *buffer = CommandBuffer;

	for (uint32 i = 0; i < CommandCount; ++i)
		{
		FakeRenderCommandFn func = *(FakeRenderCommandFn*)buffer;
		buffer += sizeof(FakeRenderCommandFn);

		uint32 size = *(uint32*)buffer;
		buffer += sizeof(uint32);

		func(buffer); // Call the render function
		buffer += size;
		}

	CommandBufferPtr = CommandBuffer;
	CommandCount = 0;
	}
