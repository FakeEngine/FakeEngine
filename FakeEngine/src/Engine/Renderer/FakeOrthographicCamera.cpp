#include "FakePch.h"
#include "FakeOrthographicCamera.h"

void FakeOrthographicCamera::RecalculateViewMatrix()
	{
	FakeMat4f transform = FakeMat4f::Translate(Position) *
		FakeMat4f::Rotate(fake_radians(Rotation), FakeVec3f(0, 0, 1));

	ViewMatrix = FakeMat4f::Inverse(transform);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

FakeOrthographicCamera::FakeOrthographicCamera(float left, float right, float bottom, float top)
	: ProjectionMatrix(FakeMat4f::OrthoOffCenter(left, right, bottom, top, -1.0f, 1.0f)), ViewMatrix(1.0f)
	{
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

void FakeOrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
	ProjectionMatrix = FakeMat4f::OrthoOffCenter(left, right, bottom, top, -1.0f, 1.0f);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

