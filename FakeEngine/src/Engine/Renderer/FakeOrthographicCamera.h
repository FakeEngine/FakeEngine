

#pragma once

// TEMP
#include <glm/glm.hpp>

class FakeOrthographicCamera
	{
	private:

		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ViewProjectionMatrix;

		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		float Rotation = 0.0f;

		void RecalculateViewMatrix();

	public:

		FakeOrthographicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3 &GetPosition() const { return Position; }
		void SetPosition(const glm::vec3 &position) { Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return Rotation; }
		void SetRotation(float rotation) { Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4 &GetViewMatrix() const { return ViewMatrix; }
		const glm::mat4 &GetProjectionMatrix() const { return ProjectionMatrix; }
		const glm::mat4 &GetViewProjectionMatrix() const { return ViewProjectionMatrix; }
	};
