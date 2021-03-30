

#pragma once

#include "FakeOrthographicCamera.h"
#include "Engine/Core/FakeTimeStep.h"
#include "Engine/Core/Events/FakeEvents.h"

class FakeOrthographicCameraController
	{
	private:
		float AspectRatio;
		float ZoomLevel = 1.0f;
		FakeOrthographicCamera Camera;

		bool Rotation;

		glm::vec3 CameraPosition = { 0.0f, 0.0f, 0.0f };
		float CameraRotation = 0.0f; // In degrees, in the anti-clockwise direction
		float CameraTranslationSpeed = 0.000000000000001f, CameraRotationSpeed = 5.0f;

		bool OnMouseScrolled(FakeMouseScrolledEvent &e);
		bool OnWindowResized(FakeWindowResizeEvent &e);

	public:

		FakeOrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnRender(FakeTimeStep ts);
		void OnEvent(FakeEvent &e);

		FakeOrthographicCamera &GetCamera() { return Camera; }
		const FakeOrthographicCamera &GetCamera() const { return Camera; }

		float GetZoomLevel() const { return ZoomLevel; }
		void SetZoomLevel(float level) { ZoomLevel = level; }
	};
