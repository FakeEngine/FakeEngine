/*****************************************************************
 * \file   FakeTimer.h
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

#include <iomanip>

enum class FakeDateFormat
	{
	NONE = 0,
	GERMAN,
	ENGLISH_US,
	ENGLISH_GB
	};

enum class FakeTimePrecision
	{
	NONE = 0,
	SECONDS,
	MILLISECONDS
	};

/**
 *
 * The Timer class can be used to measure different code parts.
 *
 * It works scope based, so the timing will automatically stop and output the timing result in the console as soon as the Instance of this class runs out of scope.
 * But it also can be stopped manually by calling the Stop function.
 *
 * ### Usage
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
 * // Automatic measurement example
 * {
 * FakeTimer timer("A Reference name");
 *
 * // some code to measure
 * }
 *
 * // Manual measurement example
 * FakeTimer timer("A Reference name");
 *
 * // some code to measure
 *
 * timer.Stop();
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
class FAKE_API FakeTimer
	{
	private:
		FakeString Name;
		FakeString OutputString;
		bool Stopped;
		std::chrono::time_point<std::chrono::steady_clock> StartPoint;

	public:

		/**
		 *
		 * The name is going to be output before the measurement value to be able to assign the measurement value to a context.
		 *
		 * @param name The name which should be shown before the measurements.
		 */
		FakeTimer(const FakeString &name);

		/**
		 *
		 * Stops the Timer automatically if it has not stopped until this point and outputs the result into the console.
		 *
		 */
		~FakeTimer();

		/**
		 * 
		 * Restarts the timer after it has been stopped.
		 * 
		 * @param name The name of the measurement.
		 */
		void Start(const FakeString &name = "");

		/**
		 *
		 * Stops the timer and outputs the result into the console.
		 *
		 */
		void Stop(bool shouldPrint = false);

		/**
		 *
		 * Returns the name of the measurement.
		 * 
		 * @return Returns the name of the measurement.
		 */
		const FakeString &GetName() const;

		/**
		 * 
		 * Returns the measurement result in a String.
		 * 
		 * @return Returns the measurement result in a String.
		 */
		const FakeString &GetOutputString() const;

		/**
		 *
		 * This function returns the current system time. It is used to calculate the current FPS and Delta Time.
		 *
		 * @return Returns the current system time.
		 */
		static double GetTime();

		/**
		 *
		 * This function returns the current Timestamp formatted into the european date and time format.
		 * It is used to output the timestamp before every Log Output in the console.
		 *
		 * @param format The DateFormat
		 * @param precision The precesion in which the time should be displayed
		 * @return Returns the current TimeStamp as a String.
		 */
		static FakeString GetTimeStamp(FakeDateFormat format = FakeDateFormat::GERMAN, FakeTimePrecision precision = FakeTimePrecision::MILLISECONDS);

		/**
		 *
		 * This function returns the current TimeStamp second as a String and it intended to be used by the clients application.
		 *
		 * @return Returns the current system time as a String.
		 */
		static FakeString GetCurrentSecond();

		/**
		 *
		 * This function returns the current TimeStamp minute as a String and it intended to be used by the clients application.
		 *
		 * @return Returns the current system time as a String.
		 */
		static FakeString GetCurrentMinute();

		/**
		 *
		 * This function returns the current TimeStamp hour as a String and it intended to be used by the clients application.
		 *
		 * @return Returns the current system time as a String.
		 */
		static FakeString GetCurrentHour();

		/**
		 *
		 * This function returns the current TimeStamp day as a String and it intended to be used by the clients application.
		 *
		 * @return Returns the current system time as a String.
		 */
		static FakeString GetCurrentDay();

		/**
		 *
		 * This function returns the current TimeStamp month as a String and it intended to be used by the clients application.
		 *
		 * @return Returns the current system time as a String.
		 */
		static FakeString GetCurrentMonth();

		/**
		 *
		 * This function returns the current TimeStamp year as a String and it intended to be used by the clients application.
		 *
		 * @return Returns the current system time as a String.
		 */
		static FakeString GetCurrentYear();
	};
