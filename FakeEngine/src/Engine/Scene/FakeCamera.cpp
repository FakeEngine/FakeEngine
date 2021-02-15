#include "FakePch.h"
#include "FakeCamera.h"

FakeCamera::FakeCamera(const FakeMat4f &projectionMatrix)
	: ProjectionMatrix(projectionMatrix)
    {
    }

FakeCamera::~FakeCamera()
	{
	}

void FakeCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
	{
	Type = ProjectionType::Perspective;
	PerspectiveFOV = verticalFOV;
	PerspectiveNear = nearClip;
	PerspectiveFar = farClip;
	}

void FakeCamera::SetOrthographic(float orthographicSize, float nearClip, float farClip)
	{
	Type = ProjectionType::Orthographic;
	OrthographicSize = orthographicSize;
	OrthographicNear = nearClip;
	OrthogtaphicFar = farClip;
	}

void FakeCamera::SetViewport(uint32 width, uint32 height)
	{
	switch (Type)
		{
		case FakeCamera::ProjectionType::Perspective:
			{
			float aspect = (float)width / (float)height;
			ProjectionMatrix = FakeMat4f::PerspectiveFOV(PerspectiveFOV, aspect, PerspectiveNear, PerspectiveFar);
			break;
			}

		case FakeCamera::ProjectionType::Orthographic:
			{
			float aspect = (float)width / (float)height;
			float w = OrthographicSize * aspect;
			float h = OrthographicSize;
			ProjectionMatrix = FakeMat4f::OrthoOffCenter(-w * 0.5f, w * 0.5f, -h * 0.5f, h * 0.5f, OrthographicNear, OrthogtaphicFar);
			break;
			}
		}
	}


