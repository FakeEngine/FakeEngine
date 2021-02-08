/*****************************************************************
 * \file   FakeApplication.h
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

#include "Engine/Core/Events/FakeEventsBase.h"
#include "Engine/Core/FakeLayer.h"
#include "Engine/Core/FakeLayerStack.h"

#include "Engine/Core/Window/FakeWindow.h"
#include "Engine/Core/Events/FakeWindowResizeEvent.h"
#include "Engine/Core/Events/FakeWindowCloseEvent.h"

 /**
  *
  * This is the main Application class which controls the Engine
  *
  */
class FakeApplication
	{
	private:
		static FakeApplication *Self;								/**< Instance to itself */

		double FrameTime = 0.0;										/**< The time of the current frame. */
		double InitialTime = -1.0;
		double ElapsedTime = 0.0;									/**< The Elapsed time of the current frame. */
		uint32 FrameCounter = 0;									/**< Current FPS */
		bool Running = true;										/**< Indicates whether the application is currently running or not. */
		bool Minimized = false;										/**< Indicates whether the application is currently minimized or not.  */
		bool EnableRendering = false;

		FakeLayerStack LayerStack;									/**< Contains all Layers implmented by the CLIENT. */
		Scope<FakeWindow> Window;									/**< The Main Window of the Application. */

		/**
		 *
		 * EventCallback which is going to be called when the main Window closes
		 * @attention This gets only called if the runtime of the Engine is being used, not the LevelEditor
		 *
		 * @param e The WindowClose Event which occurred
		 * @return whether the Event has been handled or not
		 */
		bool OnWindowClose(const FakeWindowCloseEvent &e);

		/**
		 *
		 * EventCallback which is going to called when the main Window resizes
		 * @param e The WindowResize Event which occurred
		 * @return whether the Event has been handled or not
		 */
		bool OnWindowResize(const FakeWindowResizeEvent &e);

	public:

		/**
		 * 
		 * .
		 * 
		 */
		FakeApplication();

		/**
		 *
		 * The Constructor initializes the Window, VirtualFileSystem and the Renderer.
		 *
		 * @param title The Window title.
		 * @param width The Window width.
		 * @param height The Window height.
		 */
		FakeApplication(const FakeString &title, uint32 width, uint32 height);
		
		/**
		 *
		 * The Destructor destroys the Renderer and the VirtualFileSystem in this order.
		 *
		 */
		virtual ~FakeApplication();

		/**
		 *
		 * Can be overloaded by the Client and used to initialize game-related data.
		 *
		 */
		virtual void OnInit() {}
		
		/**
		 *
		 * Can be overloaded by the Client and used to destroy game-related data.
		 *
		 */
		virtual void OnShutdown() {}

		/**
		 *
		 * Adds a Layer which is going to be implemented by the Client to the Application LayerStack.
		 *
		 * @param layer The Layer implemented by the Client
		 * @note A Layer is going to be updated once a frame and will receive any Event
		 */
		void PushLayer(FakeLayer *layer);
		
		/**
		 *
		 * Removes a Layer from the Application LayerStack.
		 *
		 * @param layer The Layer which should be removed
		 */
		void PopLayer(FakeLayer *layer);

		/**
		 *
		 * Adds a Overlay implemented by the Client to the Application LayerStack.
		 *
		 * @param overlay The Overlay which should be added
		 * @attention The difference to a Layer is that a overlay gets emplaced at the back of the Layerstack
		 */
		void PushOverlay(FakeLayer *overlay);
		
		/**
		 *
		 * Removes a Overlay implemented by the Client from the Application LayerStack.
		 *
		 * @param overlay The Overlay which should be removed
		 */
		void PopOverlay(FakeLayer *overlay);

		/**
		 *
		 * Receives any Event and calls the FakeLayer::OnEvent(FakeEvent) function in reverse order.
		 *
		 * @param e The Event which occurred
		 */
		void OnEvent(FakeEvent &e);

		/**
		 *
		 * Starts the Main Game Loop and runs until the Application should be closed.
		 *
		 */
		void Run();
		
		/**
		 *
		 * Closes the Application.
		 *
		 */
		void CloseApplication();

		/**
		 *
		 * Returns a Handle to the Application Class as a Reference.
		 *
		 * @return The Handle to the Application Class
		 */
		static FakeApplication &Get();

		/**
		 *
		 * Returns the Main Window as a Reference.
		 *
		 * @return The Main Window of the Application
		 */
		FakeWindow &GetWindow();
	};

/**
 * 
 * .
 * 
 * @return
 */
FakeApplication *fake_create_app();
