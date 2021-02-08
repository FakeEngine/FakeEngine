/*****************************************************************
 * \file   FakeTimeStep.h
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

#include "Engine/Core/FakeCore.h"

 /**
  *
  * The TimeStep class represents the Delta Time and can be used as a double or float.
  *
  */
class FAKE_API FakeTimeStep
	{
	private:
		double Time;

	public:

		/**
		 *
		 * The Constructor sets the current Delta time if one is provided or uses the default value 0.
		 *
		 * @param time Sets the current DeltaTime and 0 if no delta time is provided.
		 */
		FakeTimeStep(double time = 0.0);

		/**
		 *
		 * The double operator returns the current Delta time, formatted into a double value.
		 *
		 * @return Returns the Delta Time as a double.
		 */
		operator double() const;

		/**
		 *
		 * This function returns the current Delta Time, as a double value in seconds.
		 *
		 * @return Returns the Delta Time in seconds.
		 */
		double GetSeconds() const;

		/**
		 *
		 * This function returns the current Delta Time, as a double value in milli seconds.
		 *
		 * @return Returns the Delta Time in milli seconds.
		 */
		double GetMilliSeconds() const;
	};
