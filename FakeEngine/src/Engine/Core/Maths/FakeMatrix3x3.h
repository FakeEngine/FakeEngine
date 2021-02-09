/*****************************************************************
 * \file   FakeMatrix3x3.h
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

#include "Engine/Core/Maths/FakeMathFunctions.h"

template<typename T>
struct FAKE_API FakeMatrix3x3
	{

	union
		{
		struct
			{
			/**
			 * 
			 * .
			 * 
			 */
			T M11;
			
			/**
			 *
			 * .
			 *
			 */
			T M12;
			
			/**
			 *
			 * .
			 *
			 */
			T M13;
			
			/**
			 *
			 * .
			 *
			 */
			T M21;
			
			/**
			 *
			 * .
			 *
			 */
			T M22;
			
			/**
			 *
			 * .
			 *
			 */
			T M23;
			
			/**
			 *
			 * .
			 *
			 */
			T M31;
			
			/**
			 *
			 * .
			 *
			 */
			T M32;
			
			/**
			 *
			 * .
			 *
			 */
			T M33;
			};

		T Values[3][3];
		T Raw[9];
		};

	/**
	 *
	 * A matrix with all of its components set to zero.
	 *
	 */
	static const FakeMatrix3x3 Zero;

	/**
	 *
	 * The identity matrix.
	 *
	 */
	static const FakeMatrix3x3 Identity;

	FakeMatrix3x3()
		{
		M11 = static_cast<T>(0);
		M12 = static_cast<T>(0);
		M13 = static_cast<T>(0);
		M21 = static_cast<T>(0);
		M22 = static_cast<T>(0);
		M23 = static_cast<T>(0);
		M31 = static_cast<T>(0);
		M32 = static_cast<T>(0);
		M33 = static_cast<T>(0);
		}

	FakeMatrix3x3(T value)
		{
		M11 = value;
		M12 = static_cast<T>(0);
		M13 = static_cast<T>(0);
		M21 = static_cast<T>(0);
		M22 = value;
		M23 = static_cast<T>(0);
		M31 = static_cast<T>(0);
		M32 = static_cast<T>(0);
		M33 = value;
		}

	FakeMatrix3x3(T m11, T m12, T m13, T m21, T m22, T m23, T m31, T m32, T m33)
		: M11(m11), M12(m12), M13(m13), M21(m21), M22(m22), M23(m23), M31(m31), M32(m32), M33(m33)
		{
		}

	FakeMatrix3x3(T values[9])
		{
		memcpy(Raw, values, 9 * sizeof(T));
		}

	FakeMatrix3x3(T values[3][3])
		{
		memcpy(Raw, values, 9 * sizeof(T));
		}

	/**
	 * 
	 * copy constructor.
	 * 
	 * @param The matrix to copy.
	 */
	FakeMatrix3x3(const FakeMatrix3x3&) = default;

	/**
	 * 
	 * copy operator.
	 * 
	 * @param The matrix to copy.
	 * @return Returns the copied instance.
	 */
	FakeMatrix3x3 &operator=(const FakeMatrix3x3&) = default;

	/**
	 *
	 * Converts the matrix to a String.
	 * 
	 * @return Returns the matrix as a String.
	 */
	FakeString ToString() const
		{
		FakeString result;
		result << M11 << ", " << M12 << ", " << M13 << ",\n";
		result << M21 << ", " << M22 << ", " << M23 << ",\n";
		result << M31 << ", " << M32 << ", " << M33 << "\n";
		return result;
		}



	/**
	 *
	 * Overloaded dereferncing operator to get the matrix data as an array.
	 *
	 * @return Returns an array filled with the content of the matrix.
	 */
	T *operator*()
		{
		static T arr[9];

		for (int32 i = 0; i < 9; ++i)
			arr[i] = Raw[i];

		return arr;
		}

	/**
	 *
	 * Overloaded dereferncing operator to get the matrix data as an array.
	 *
	 * @return Returns an array filled with the content of the matrix.
	 */
	const T *operator*() const
		{
		static T arr[9];

		for (int32 i = 0; i < 9; ++i)
			arr[i] = Raw[i];

		return arr;
		}

	/**
	 *
	 * Overloaded Array Indexing operator to access the content of the matrix directly like an array.
	 *
	 * @param index The index where the matrix instance should be accessed.
	 * @return Returns the content at the specified index.
	 */
	T &operator[](uint32 index)
		{
		FAKE_ASSERT(index < 9);
		return Raw[index];
		}

	/**
	 *
	 * Overloaded Array Indexing operator to access the content of the matrix directly like an array.
	 *
	 * @param index The index where the matrix instance should be accessed.
	 * @return Returns the content at the specified index.
	 */
	const T &operator[](uint32 index) const
		{
		FAKE_ASSERT(index < 9);
		return Raw[index];
		}

	/**
	 * 
	 * Overloaded << operator to print the Matrix into a output stream.
	 * 
	 * @param stream The output stream.
	 * @param matrix The matrix to print.
	 * @return Returns the modified output stream.
	 */
	friend std::ostream &operator<<(std::ostream &stream, const FakeMatrix3x3 &matrix)
		{
		stream << matrix.M11 << ", " << matrix.M12 << ", " << matrix.M13 << "," << std::endl;
		stream << matrix.M21 << ", " << matrix.M22 << ", " << matrix.M23 << "," << std::endl;
		stream << matrix.M31 << ", " << matrix.M32 << ", " << matrix.M33 << std::endl;
		return stream;
		}
	};

template<typename T>
const FakeMatrix3x3<T> FakeMatrix3x3<T>::Zero(static_cast<T>(0));

template<typename T>
const FakeMatrix3x3<T> FakeMatrix3x3<T>::Identity(static_cast<T>(1));

typedef FakeMatrix3x3<double> FakeMat3d;
typedef FakeMatrix3x3<float> FakeMat3f;
typedef FakeMatrix3x3<int32> FakeMat3i;
typedef FakeMatrix3x3<long> FakeMat3l;
typedef FakeMatrix3x3<short> FakeMat3s;
typedef FakeMatrix3x3<bool> FakeMat3b;
