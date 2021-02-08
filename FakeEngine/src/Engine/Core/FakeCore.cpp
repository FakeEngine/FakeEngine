#include "FakePch.h"
#include "FakeCore.h"

static FakeAllocationMetrics AllocationMetrics;

void *operator new(size_t size)
	{
	AllocationMetrics.TotalAllocated += (uint32)size;
	return malloc(size);
	}

void operator delete(void *memory, size_t size)
	{
	AllocationMetrics.TotalFreed += (uint32)size;
	free(memory);
	}

void fake_print_current_memory_usage()
	{
	FAKE_LOG_TRACE("Memory Usage: %d bytes (%d bytes allocated, %d bytes freed)", AllocationMetrics.CurrentUsage(), AllocationMetrics.TotalAllocated, AllocationMetrics.TotalFreed);
	}
