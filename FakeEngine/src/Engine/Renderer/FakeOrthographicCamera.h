

#pragma once

#include "Engine/Core/Maths/FakeMaths.h"

class FakeOrthographicCamera
	{
	private:

		FakeMat4f ProjectionMatrix;
		FakeMat4f ViewMatrix;
		FakeMat4f ViewProjectionMatrix;

		FakeVec3f Position = { 0.0f, 0.0f, 0.0f };
		float Rotation = 0.0f;

		void RecalculateViewMatrix();

	public:

		FakeOrthographicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		const FakeVec3f &GetPosition() const { return Position; }
		void SetPosition(const FakeVec3f &position) { Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return Rotation; }
		void SetRotation(float rotation) { Rotation = rotation; RecalculateViewMatrix(); }

		const FakeMat4f &GetViewMatrix() const { return ViewMatrix; }
		const FakeMat4f &GetProjectionMatrix() const { return ProjectionMatrix; }
		const FakeMat4f &GetViewProjectionMatrix() const { return ViewProjectionMatrix; }
	};
