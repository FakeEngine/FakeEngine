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

	public:

		virtual void OnAttach() override
			{
			FakeMat2f mat(1, -1, 3, 4);
			mat.Inverse();
			std::cout << mat << std::endl;

			LogoTex = FakeTexture2D::Create("assets/textures/Logo.png");
			}

		virtual void OnDetach() override
			{
			}

		virtual void OnEvent(FakeEvent &e) override
			{
			}

		virtual void OnRender(FakeTimeStep ts) override
			{
			FakeRenderer2D::BeginScene();
			FakeRenderer2D::DrawQuad({ 2.0f, 0.0f, 0.0f }, { 0.5f, 0.5f }, 45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
			FakeRenderer2D::DrawTexture({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, 90.0f, LogoTex, 1.0f, { 1.0f, 1.0f, 1.0f, 1.0f });
			FakeRenderer2D::EndScene();
			}
	};

