/*****************************************************************
 * \file   Fake.h
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

// Core
#include "Engine/Core/FakeApplication.h"
#include "Engine/Core/FakeReference.h"
#include "Engine/Core/FakeEntryPoint.h"
#include "Engine/Core/FakeAssert.h"
#include "Engine/Core/FakeCore.h"
#include "Engine/Core/FakeGlobals.h"
#include "Engine/Core/FakeLayer.h"
#include "Engine/Core/FakeLayerStack.h"
#include "Engine/Core/FakeLog.h"
#include "Engine/Core/FakeRandom.h"
#include "Engine/Core/FakeSingleton.h"
#include "Engine/Core/FakeTimer.h"
#include "Engine/Core/FakeTimeStep.h"
#include "Engine/Core/FakeVersion.h"
#include "Engine/Core/FakeFileSystem.h"
#include "Engine/Core/FakeVirtualFileSystem.h"

// Allocators
#include "Engine/Core/FakeAllocator.h"

// Defines
#include "Engine/Core/Defines/FakeDefines.h"

// Events
#include "Engine/Core/Events/FakeEvents.h"

// Window
#include "Engine/Core/Window/FakeConsole.h"
#include "Engine/Core/Window/FakeCursor.h"
#include "Engine/Core/Window/FakeFileDialogue.h"
#include "Engine/Core/Window/FakeFileDialogueFilter.h"
#include "Engine/Core/Window/FakeFileMenu.h"
#include "Engine/Core/Window/FakeFileMenuBar.h"
#include "Engine/Core/Window/FakeInput.h"
#include "Engine/Core/Window/FakePopupMenu.h"
#include "Engine/Core/Window/FakePopupMenuItem.h"
#include "Engine/Core/Window/FakeWindow.h"

// DataTypes
#include "Engine/Core/DataTypes/FakeDataTypes.h"

// Maths
#include "Engine/Core/Maths/FakeMaths.h"

// Utils
#include "Engine/Utils/FakeUtils.h"

// Renderer
#include "Engine/Renderer/FakeRenderingContext.h"
#include "Engine/Renderer/FakeRenderer.h"
#include "Engine/Renderer/FakeRenderer2D.h"
#include "Engine/Renderer/FakeSceneRenderer.h"
#include "Engine/Renderer/FakePipeline.h"
#include "Engine/Renderer/FakeVertexBuffer.h"
#include "Engine/Renderer/FakeVertexBufferLayout.h"
#include "Engine/Renderer/FakeIndexBuffer.h"
#include "Engine/Renderer/FakeFramebuffer.h"
#include "Engine/Renderer/FakeFramebufferPool.h"
#include "Engine/Renderer/FakeRenderPass.h"
#include "Engine/Renderer/FakeTexture2D.h"
#include "Engine/Renderer/FakeTextureCube.h"
#include "Engine/Renderer/FakeShader.h"
#include "Engine/Renderer/FakeShaderLibrary.h"
#include "Engine/Renderer/FakeMesh.h"
#include "Engine/Renderer/FakeMeshFactory.h"
#include "Engine/Renderer/FakeMaterial.h"
#include "Engine/Renderer/FakeMaterialInstance.h"

// Net
#include "Engine/Net/FakeNet.h"

// Scene
#include "Engine/Scene/FakeCamera.h"
#include "Engine/Scene/FakeEditorCamera.h"
#include "Engine/Scene/FakeEntity.h"
#include "Engine/Scene/FakeScene.h"

