#include "FakePch.h"
#include "FakeOrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

void FakeOrthographicCamera::RecalculateViewMatrix()
	{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), glm::vec3(0, 0, 1));

	ViewMatrix = glm::inverse(transform);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

FakeOrthographicCamera::FakeOrthographicCamera(float left, float right, float bottom, float top)
	: ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), ViewMatrix(1.0f)
	{
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

void FakeOrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
	ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

