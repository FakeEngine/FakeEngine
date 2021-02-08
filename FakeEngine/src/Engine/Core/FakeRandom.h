/*****************************************************************
 * \file   FakeRandom.h
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

#include <random>

/**
 *
 * This class can be used to generate random numbers inside the Engine or the Client.
 *
 * ### Usage
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
 * FakeRandom::Init();
 * float randomValue = FakeRandom::Float();
 * or
 * double randomValue = FakeRandom::Double();
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
class FAKE_API FakeRandom
	{
	private:
		static std::mt19937 RandomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> Distribution;

	public:

		/**
		 *
		 * Initializes the seed to have a collection of random numbers to choose from.
		 *
		 */
		static void Init();

		/**
		 *
		 * Picks a random number from the seed and returns it as a float value.
		 *
		 * @return Returns a random number as a float value.
		 */
		static float Float();

		/**
		 *
		 * Picks a random number from the seed and returns it as a double value.
		 *
		 * @return Returns a random number as a double value.
		 */
		static double Double();
	};
