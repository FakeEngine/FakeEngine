#include "FakePch.h"
#include "FakeLayer.h"

FakeLayer::FakeLayer(const FakeString &debugName)
	: DebugName(debugName)
	{
	}

FakeLayer::~FakeLayer()
	{
	}

const FakeString &FakeLayer::GetName()
	{
	return DebugName;
	}

void FakeLayer::OnAttach()
	{
	}

void FakeLayer::OnDetach()
	{
	}

void FakeLayer::OnRender(FakeTimeStep ts)
	{
	}

void FakeLayer::OnEvent(FakeEvent &e)
	{
	}
