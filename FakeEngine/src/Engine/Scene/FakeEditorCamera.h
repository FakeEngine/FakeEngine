/*****************************************************************
 * \file   FakeEditorCamera.h
 * \brief  
 * 
 * \author Can Karka
 * \date   February 2021
 * 
 * Copyright (C) 2021 Can Karka
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *********************************************************************/

#pragma once

#include "Engine/Core/Events/FakeEvents.h"
#include "Engine/Core/Maths/FakeMaths.h"
#include "Engine/Core/FakeTimeStep.h"

/**
 * 
 * .
 * 
 */
class FAKE_API FakeEditorCamera
	{
	private:
		
		FakeMat4f ProjectionMatrix;
		FakeMat4f ViewMatrix;

		FakeVec3f Position, Rotation, FocalPoint;
		bool IsPanning, IsRotating;

		FakeVec2f InitialMousePosition;
		FakeVec3f InitialFocalPoint, InitialRotation;

		float Distance;
		float Pitch, Yaw;

		uint32 ViewportWidth = 1280, ViewportHeight = 720;

		void UpdateCameraView();
		FakeVec3f CalculatePosition();

		bool OnMouseScrolled(const FakeMouseScrolledEvent &e);

		void MousePan(const FakeVec2f &delta);
		void MouseRotate(const FakeVec2f &delta);
		void MouseZoom(float delta);

		std::pair<float, float> GetPanSpeed() const;
		float GetRotationSpeed() const;
		float GetZoomSpeed() const;

	public:

		FakeEditorCamera() = default;

		FakeEditorCamera(const FakeMat4f &projectionMatrix);

		void Focus();
		void OnRender(FakeTimeStep ts);
		void OnEvent(FakeEvent &e);

		const FakeVec3f &GetPosition() { return Position; }
		float GetPitch() const { return Pitch; }
		float GetYaw() const { return Yaw; }
		float GetDistance() const { return Distance; }
		void SetDistance(float distance) { Distance = distance; }

		void SetViewport(uint32 width, uint32 height) { ViewportWidth = width; ViewportHeight = height; }

		const FakeMat4f &GetViewMatrix() const { return ViewMatrix; }
		const FakeMat4f &GetProjectionMatrix() const { return ProjectionMatrix; }
		const FakeMat4f &GetViewProjectionMatrix() const { return ProjectionMatrix * ViewMatrix; }

		FakeVec3f GetUpDirection();
		FakeVec3f GetRightDirection();
		FakeVec3f GetForwardDirection();
		FakeQuatf GetOrientation() const;
	};
