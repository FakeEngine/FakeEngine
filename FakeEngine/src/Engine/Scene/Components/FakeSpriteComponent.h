#pragma once

#include "Engine/Core/Maths/FakeMaths.h"

struct FakeSpriteComponent
	{
	FakeVec4f Color{ 1.0f, 1.0f, 1.0f, 1.0f };

	FakeSpriteComponent() = default;
	FakeSpriteComponent(const FakeSpriteComponent &) = default;
	FakeSpriteComponent(const FakeVec4f &color);

	};

