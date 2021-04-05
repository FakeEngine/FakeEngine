#pragma once

#include "Engine/Core/Maths/FakeMaths.h"

struct FakeTransformComponent
	{
	FakeVec3f Translation = { 0.0f, 0.0f, 0.0f };
	FakeVec3f Rotation = { 0.0f, 0.0f, 0.0f };
	FakeVec3f Scale = { 1.0f, 1.0f, 1.0f };

	FakeTransformComponent() = default;
	FakeTransformComponent(const FakeTransformComponent &) = default;
	FakeTransformComponent(const FakeVec3f &translation);

	FakeMat4f GetTransform() const;
	};

