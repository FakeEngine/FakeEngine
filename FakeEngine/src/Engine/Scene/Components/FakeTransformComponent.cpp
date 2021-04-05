#include "FakePch.h"
#include "FakeTransformComponent.h"

FakeTransformComponent::FakeTransformComponent(const FakeVec3f &translation)
	: Translation(translation)
	{
	}

FakeMat4f FakeTransformComponent::GetTransform() const
	{
	FakeMat4f rotation = FakeQuatf::ToMatrix4(FakeQuatf(Rotation));
	FakeMat4f transform = FakeMat4f::Translate(Translation) * rotation * FakeMat4f::Scale(Scale);
	return transform;
	}
