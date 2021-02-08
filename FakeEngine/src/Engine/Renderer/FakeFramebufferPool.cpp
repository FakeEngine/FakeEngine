#include "FakePch.h"
#include "FakeFramebufferPool.h"

FakeFramebufferPool *FakeFramebufferPool::Instance = new FakeFramebufferPool();

FakeFramebufferPool::FakeFramebufferPool(uint32 maxFBs)
	{
	}

FakeFramebufferPool::~FakeFramebufferPool()
	{
	}

std::weak_ptr<FakeFramebuffer> FakeFramebufferPool::AllocateBuffer()
	{
	return std::weak_ptr<FakeFramebuffer>();
	}

void FakeFramebufferPool::Add(const FakeRef<FakeFramebuffer> &framebuffer)
	{
	FramebufferPool.push_back(framebuffer);
	}

std::vector<FakeRef<FakeFramebuffer>> &FakeFramebufferPool::GetAll()
	{
	return FramebufferPool;
	}

const std::vector<FakeRef<FakeFramebuffer>> &FakeFramebufferPool::GetAll() const
	{
	return FramebufferPool;
	}

FakeFramebufferPool *FakeFramebufferPool::GetGlobal()
	{
	return Instance;
	}
