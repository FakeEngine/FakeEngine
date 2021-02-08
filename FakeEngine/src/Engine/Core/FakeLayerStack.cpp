#include "FakePch.h"
#include "FakeLayerStack.h"

FakeLayerStack::FakeLayerStack()
	{
	}

FakeLayerStack::~FakeLayerStack()
	{
	for (FakeLayer *layer : Layers)
		delete layer;
	}

void FakeLayerStack::PushLayer(FakeLayer *layer)
	{
	Layers.emplace(Layers.begin() + LayerInsertIndex, layer);
	++LayerInsertIndex;
	}

void FakeLayerStack::PopLayer(FakeLayer *layer)
	{
	auto it = std::find(Layers.begin(), Layers.end(), layer);
	if (it != Layers.end())
		{
		Layers.erase(it);
		--LayerInsertIndex;
		}
	}

void FakeLayerStack::PushOverlay(FakeLayer *overlay)
	{
	Layers.emplace_back(overlay);
	}

void FakeLayerStack::PopOverlay(FakeLayer *overlay)
	{
	auto it = std::find(Layers.begin(), Layers.end(), overlay);
	if (it != Layers.end())
		{
		Layers.erase(it);
		}
	}

std::vector<FakeLayer*>::iterator FakeLayerStack::begin()
	{
	return Layers.begin();
	}

std::vector<FakeLayer*>::iterator FakeLayerStack::end()
	{
	return Layers.end();
	}

std::vector<FakeLayer*>::const_iterator FakeLayerStack::begin() const
	{
	return Layers.begin();
	}

std::vector<FakeLayer*>::const_iterator FakeLayerStack::end() const
	{
	return Layers.end();
	}

