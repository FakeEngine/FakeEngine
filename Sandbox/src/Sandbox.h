/*****************************************************************
 * \file   Sandbox.h
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

#include "ExampleLayer.h"

class Sandbox : public FakeApplication
	{
	public:
		Sandbox(const FakeString &title, uint32 width, uint32 height)
			: FakeApplication(title, width, height)
			{
			}

		virtual void OnInit() override
			{
			PushLayer(new ExampleLayer());
			}

		virtual void OnShutdown() override
			{

			}
	};

