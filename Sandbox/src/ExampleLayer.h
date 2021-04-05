/*****************************************************************
 * \file   ExampleLayer.h
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

#include <Fake.h>

class ExampleLayer : public FakeLayer
	{
	private:
		FakeRef<FakeTexture2D> LogoTex;
		FakeOrthographicCameraController CameraController;

	public:

		ExampleLayer()
			: CameraController(1280.0f / 720.0f, true)
			{
			}

		virtual void OnAttach() override
			{
			LogoTex = FakeTexture2D::Create("assets/textures/Logo.png");
			}

		virtual void OnDetach() override
			{
			}

		virtual void OnEvent(FakeEvent &e) override
			{
			CameraController.OnEvent(e);
			}

		virtual void OnRender(FakeTimeStep ts) override
			{
			CameraController.OnRender(ts);

			FakeRenderer2D::BeginScene({ 1280.0f, 720.0f });
			FakeRenderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		//	FakeRenderer2D::DrawTexture({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, LogoTex);
			FakeRenderer2D::EndScene();
			}
	};

