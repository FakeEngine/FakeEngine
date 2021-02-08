/*****************************************************************
 * \file   FakeVersion.h
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

/**
 * 
 * .
 * 
 */
class FAKE_API FakeVersion
	{
	private:
		int32 _Major;
		int32 _Minor;
		int32 _Build;
		int32 _Revision;

	public:

		/**
		 *
		 * .
		 *
		 */
		FakeVersion();

		/**
		 *
		 * .
		 *
		 * @param minor
		 * @param major
		 * @param build
		 * @param revision
		 */
		FakeVersion(int32 minor, int32 major, int32 build, int32 revision);

		/**
		 *
		 * .
		 *
		 * @param minor
		 * @param major
		 * @param build
		 */
		FakeVersion(int32 minor, int32 major, int32 build);

		/**
		 *
		 * .
		 *
		 * @param minor
		 * @param major
		 */
		FakeVersion(int32 minor, int32 major);

		/**
		 *
		 * .
		 *
		 * @return
		 */
		int32 Build() const;

		/**
		 *
		 * .
		 *
		 * @return
		 */
		int32 Minor() const;

		/**
		 *
		 * .
		 *
		 * @return
		 */
		int16 MinorRevision() const;

		/**
		 *
		 * .
		 *
		 * @return
		 */
		int32 Major() const;

		/**
		 *
		 * .
		 *
		 * @return
		 */
		int16 MajorRevision() const;

		/**
		 *
		 * .
		 *
		 * @return
		 */
		int32 Revision() const;

		/**
		 *
		 * .
		 *
		 * @param other
		 * @return
		 */
		int32 CompareTo(const FakeVersion &other) const;

		/**
		 *
		 * .
		 *
		 * @param other
		 * @return
		 */
		bool Equals(const FakeVersion &other) const;

		/**
		 *
		 * .
		 *
		 * @return
		 */
		FakeString ToString() const;

		/**
		 *
		 * .
		 *
		 * @param fieldCount
		 * @return
		 */
		FakeString ToString(int32 fieldCount) const;

		/**
		 *
		 * .
		 *
		 * @param versionStr
		 * @param outValue
		 * @return
		 */
		static bool FromString(const FakeString &versionStr, FakeVersion *outValue);

		/**
		 *
		 * .
		 *
		 * @param other
		 * @return
		 */
		bool operator==(const FakeVersion &other) const;

		/**
		 *
		 * .
		 *
		 * @param other
		 * @return
		 */
		bool operator!=(const FakeVersion &other) const;

		/**
		 *
		 * .
		 *
		 * @param other
		 * @return
		 */
		bool operator<(const FakeVersion &other) const;

		/**
		 *
		 * .
		 *
		 * @param other
		 * @return
		 */
		bool operator<=(const FakeVersion &other) const;

		/**
		 *
		 * .
		 *
		 * @param other
		 * @return
		 */
		bool operator>(const FakeVersion &other) const;

		/**
		 *
		 * .
		 *
		 * @param other
		 * @return
		 */
		bool operator>=(const FakeVersion &other) const;
	};
