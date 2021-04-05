#pragma once

#include "Engine/Scene/FakeCamera.h"

struct FakeCameraComponent
	{
	FakeCamera Camera;
	bool Primary = true;
	bool FixedAspectRatio = false;

	FakeCameraComponent() = default;
	FakeCameraComponent(const FakeCameraComponent&) = default;
	};

