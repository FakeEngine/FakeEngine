/*****************************************************************
 * \file   FakeMatrix2x2.h
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
#include "Engine/Core/Maths/FakeVector2.h"
#include "Engine/Core/Maths/FakeVector3.h"
#include "Engine/Core/Maths/FakeVector4.h"

template<typename T>
struct FAKE_API FakeMatrix2x2
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
			T M21;
			
			/**
			 * 
			 * .
			 * 
			 */
			T M22;
			};

		T Values[2][2];
		T Raw[4];
		};

	/**
	 * 
	 * A matrix with all of its components set to zero.
	 * 
	 */
	static const FakeMatrix2x2 Zero;

	/**
	 * 
	 * The identity matrix.
	 * 
	 */
	static const FakeMatrix2x2 Identity;

	FakeMatrix2x2()
		{
		M11 = static_cast<T>(0);
		M12 = static_cast<T>(0);
		M21 = static_cast<T>(0);
		M22 = static_cast<T>(0);
		}

	FakeMatrix2x2(T value)
		{
		M11 = value;
		M12 = static_cast<T>(0);
		M21 = static_cast<T>(0);
		M22 = value;
		}

	FakeMatrix2x2(T m11, T m12, T m21, T m22)
		: M11(m11), M12(m12), M21(m21), M22(m22)
		{
		}

	FakeMatrix2x2(T values[4])
		{
		memcpy(Raw, values, 4 * sizeof(T));
		}

	FakeMatrix2x2(T values[2][2])
		{
		memcpy(Raw, values, 4 * sizeof(T));
		}

	FakeMatrix2x2(const FakeVector2<T> &v1, T m21, T m22)
		: M11(v1.X), M12(v1.Y), M21(m21), M22(m22)
		{
		}

	FakeMatrix2x2(const FakeVector2<T> &v1, const FakeVector2<T> &v2)
		: M11(v1.X), M12(v1.Y), M21(v2.X), M22(v2.Y)
		{
		}

	FakeMatrix2x2(const FakeVector3<T> &v1, T m22)
		: M11(v1.X), M12(v1.Y), M21(v1.Z), M22(m22)
		{
		}

	FakeMatrix2x2(const FakeVector4<T> &v)
		: M11(v.X), M12(v.Y), M21(v.Z), M22(v.W)
		{
		}

	/**
	 * 
	 * copy constructor.
	 * 
	 * @param The matrix to copy.
	 */
	FakeMatrix2x2(const FakeMatrix2x2&) = default;

	/**
	 * 
	 * copy operator.
	 * 
	 * @param The matrix to copy.
	 * @return Returns the copied instance.
	 */
	FakeMatrix2x2 &operator=(const FakeMatrix2x2&) = default;

	/**
	 *
	 * Converts the matrix to a String.
	 * 
	 * @return Returns the matrix as a String.
	 */
	FakeString ToString() const
		{
		FakeString result;
		result << M11 << ", " << M12 << ",\n";
		result << M21 << ", " << M22 << "\n";
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
		static T arr[4];

		for (int32 i = 0; i < 4; ++i)
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
		static T arr[4];

		for (int32 i = 0; i < 4; ++i)
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
		FAKE_ASSERT(index < 4);
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
		FAKE_ASSERT(index < 4);
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
	friend std::ostream &operator<<(std::ostream &stream, const FakeMatrix2x2 &matrix)
		{
		stream << matrix.M11 << ", " << matrix.M12 << "," << std::endl;
		stream << matrix.M21 << ", " << matrix.M22 << std::endl;
		return stream;
		}
	};

template<typename T>
const FakeMatrix2x2<T> FakeMatrix2x2<T>::Zero(static_cast<T>(0));

template<typename T>
const FakeMatrix2x2<T> FakeMatrix2x2<T>::Identity(static_cast<T>(1));

typedef FakeMatrix2x2<double> FakeMat2d;
typedef FakeMatrix2x2<float> FakeMat2f;
typedef FakeMatrix2x2<int32> FakeMat2i;
typedef FakeMatrix2x2<short> FakeMat2s;
typedef FakeMatrix2x2<long> FakeMat2l;
typedef FakeMatrix2x2<bool> FakeMat2b;

