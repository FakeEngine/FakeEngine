/*****************************************************************
 * \file   FakeCamera.h
 * \brief  
 * 
 * \author Can Karka
 * \date   January 2021
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

#include "Engine/Core/Maths/FakeMaths.h"

/**
 * 
 * .
 * 
 */
class FAKE_API FakeCamera
	{
	public:

		enum class ProjectionType { Perspective = 0, Orthographic = 1 };

	private:
		FakeMat4f ProjectionMatrix;
		float Exposure = 0.0f;
		ProjectionType Type = ProjectionType::Orthographic;

		float PerspectiveFOV = fake_radians(45.0f);
		float PerspectiveNear = 0.01f;
		float PerspectiveFar = 10000.0f;

		float OrthographicSize = 10.0f;
		float OrthographicNear = -1.0f;
		float OrthogtaphicFar = 1.0f;

	public:

		FakeCamera() = default;

		FakeCamera(const FakeMat4f & projectionMatrix);
		virtual ~FakeCamera();

		const FakeMat4f &GetProjectionMatrix() const { return ProjectionMatrix; }
		void SetProjectionMatrix(const FakeMat4f & projectionMatrix) { ProjectionMatrix = projectionMatrix; }

		float GetExposure() const { return Exposure; }
		float &GetExposure() { return Exposure; }

		void SetPerspectiveFOV(float verticalFOV) { PerspectiveFOV = fake_radians(verticalFOV); }
		float GetPerspectiveFOV() const { return fake_degrees(PerspectiveFOV); }

		void SetPerspectiveNearClip(float nearClip) { PerspectiveNear = nearClip; }
		float GetPerspectiveNearClip() const { return PerspectiveNear; }

		void SetPerspectiveFar(float farClip) { PerspectiveFar = farClip; }
		float GetPerspectiveFar() const { return PerspectiveFar; }

		void SetOrthographicSize(float size) { OrthographicSize = size; }
		float GetOrthographicSize() const { return OrthographicSize; }

		void SetOrthographicNear(float nearClip) { OrthographicNear = nearClip; }
		float GetOrthographicNear() const { return OrthographicNear; }

		void SetOrthographicFar(float farClip) { OrthogtaphicFar = farClip; }
		float GetOrthographicFar() const { return OrthogtaphicFar; }

		void SetPerspective(float verticalFOV, float nearClip, float farClip);
		void SetOrthographic(float orthographicSize, float nearClip, float farClip);
		void SetViewport(uint32 width, uint32 height);
	};
