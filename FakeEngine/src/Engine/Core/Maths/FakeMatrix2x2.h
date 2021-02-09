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
	FakeMatrix2x2(const FakeMatrix2x2 &other)
		{
		M11 = other.M11;
		M12 = other.M12;
		M21 = other.M21;
		M22 = other.M22;
		}

	/**
	 * 
	 * copy operator.
	 * 
	 * @param The matrix to copy.
	 * @return Returns the copied instance.
	 */
	FakeMatrix2x2 &operator=(const FakeMatrix2x2 &other)
		{
		M11 = other.M11;
		M12 = other.M12;
		M21 = other.M21;
		M22 = other.M22;
		return *this;
		}

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
	 * .
	 * 
	 * @param values
	 * @param index
	 */
	void SetRow(const FakeVector2<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			M11 = values.X;
			M12 = values.Y;
			}
		else if (index == 1)
			{
			M21 = valuex.X;
			M22 = valuex.Y;
			}
		}

	/**
	 * 
	 * .
	 * 
	 * @param index
	 * @return 
	 */
	FakeVector2<T> GetRow(uint32 index = 0) const
		{
		if (index == 0)
			{
			return FakeVector2<T>(M11, M12);
			}
		else if (index == 1)
			{
			return FakeVector2<T>(M21, M22);
			}

		return FakeVector2<T>::Zero;
		}

	/**
	 * 
	 * .
	 * 
	 * @param values
	 * @param index
	 */
	void SetColumn(const FakeVector2<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			M11 = values.X;
			M21 = values.Y;
			}
		else if (index == 1)
			{
			M12 = values.X;
			M22 = values.Y;
			}
		}

	/**
	 * 
	 * .
	 * 
	 * @param index
	 * @return 
	 */
	FakeVector2<T> GetColumn(uint32 index = 0) const
		{
		if (index == 0)
			{
			return FakeVector2<T>(M11, M21);
			}
		else if (index == 1)
			{
			return FakeVector2<T>(M12, M22);
			}

		return FakeVector2<T>::Zero;
		}

	/**
	 * 
	 * .
	 * 
	 * @return 
	 */
	bool IsIdentity() const
		{
		return *this == Identity;
		}

	/**
	 * 
	 * .
	 * 
	 * @return 
	 */
	T GetDeterminant() const
		{
		return (M11 * M22) - (M12 * M21);
		}

	/**
	 * 
	 * .
	 * 
	 */
	void Inverse()
		{
		Inverse(*this, *this);
		}

	/**
	 * 
	 * .
	 * 
	 */
	void Transpose()
		{
		Transpose(*this, *this);
		}

	/**
	 * 
	 * .
	 * 
	 * @param value
	 * @param result
	 */
	static void Inverse(const FakeMatrix2x2 &value, FakeMatrix2x2 &result)
		{
		T det = (value.M11 * value.M22) - (value.M12 * value.M21);
		if (FAKE_ABS(det) < FAKE_ZERO_TOLERANCE)
			{
			result = Zero;
			return;
			}

		T inv = static_cast<T>(1) / det;
		result.M11 = +value.M22 * inv;
		result.M12 = -value.M12 * inv;
		result.M21 = -value.M21 * inv;
		result.M22 = +value.M11 * inv;
		}

	/**
	 * 
	 * .
	 * 
	 * @param value
	 * @return 
	 */
	static FakeMatrix2x2 Inverse(const FakeMatrix2x2 &value)
		{
		FakeMatrix2x2 result;
		Inverse(value, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param value
	 * @param result
	 */
	static void Transpose(const FakeMatrix2x2 &value, FakeMatrix2x2 &result)
		{
		result.M11 = value.M11;
		result.M12 = value.M21;
		result.M21 = value.M12;
		result.M22 = value.M22;
		}

	/**
	 * 
	 * .
	 * 
	 * @param value
	 * @return 
	 */
	static FakeMatrix2x2 Transpose(const FakeMatrix2x2 &value)
		{
		FakeMatrix2x2 result;
		Transpose(value, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @param result
	 */
	static void Add(const FakeMatrix2x2 &left, const FakeMatrix2x2 &right, FakeMatrix2x2 &result)
		{
		result.M11 = left.M11 + right.M11;
		result.M12 = left.M12 + right.M12;
		result.M21 = left.M21 + right.M21;
		result.M22 = left.M22 + right.M22;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix2x2 Add(const FakeMatrix2x2 &left, const FakeMatrix2x2 &right)
		{
		FakeMatrix2x2 result;
		Add(left, right, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @param result
	 */
	static void Subtract(const FakeMatrix2x2 &left, const FakeMatrix2x2 &right, FakeMatrix2x2 &result)
		{
		result.M11 = left.M11 - right.M11;
		result.M12 = left.M12 - right.M12;
		result.M21 = left.M21 - right.M21;
		result.M22 = left.M22 - right.M22;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix2x2 Subtract(const FakeMatrix2x2 &left, const FakeMatrix2x2 &right)
		{
		FakeMatrix2x2 result;
		Subtract(left, right, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @param result
	 */
	static void Multiply(const FakeMatrix2x2 &left, const FakeMatrix2x2 &right, FakeMatrix2x2 &result)
		{
		result.M11 = left.M11 * right.M11;
		result.M12 = left.M12 * right.M21;
		result.M21 = left.M21 * right.M12;
		result.M22 = left.M22 * right.M22;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix2x2 Multiply(const FakeMatrix2x2 &left, const FakeMatrix2x2 &right)
		{
		FakeMatrix2x2 result;
		Multiply(left, right, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @param result
	 */
	static void Multiply(const FakeMatrix2x2 &left, T right, FakeMatrix2x2 &result)
		{
		result.M11 = left.M11 * right;
		result.M12 = left.M12 * right;
		result.M21 = left.M21 * right;
		result.M22 = left.M22 * right;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix2x2 Multiply(const FakeMatrix2x2 &left, T right)
		{
		FakeMatrix2x2 result;
		Multiply(left, right, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @param result
	 */
	static void Divide(const FakeMatrix2x2 &left, const FakeMatrix2x2 &right, FakeMatrix2x2 &result)
		{
		// TODO: check right

		result.M11 = left.M11 / right.M11;
		result.M12 = left.M12 / right.M12;
		result.M21 = left.M21 / right.M21;
		result.M22 = left.M22 / right.M22;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix2x2 Divide(const FakeMatrix2x2 &left, const FakeMatrix2x2 &right)
		{
		FakeMatrix2x2 result;
		Divide(left, right, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @param result
	 */
	static void Divide(const FakeMatrix2x2 &left, T right, FakeMatrix2x2 &result)
		{
		FAKE_ASSERT(!fake_is_zero(right));
		const T inv = static_cast<T>(1) / right;

		result.M11 = left.M11 * inv;
		result.M12 = left.M12 * inv;
		result.M21 = left.M21 * inv;
		result.M22 = left.M22 * inv;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix2x2 Divide(const FakeMatrix2x2 &left, T right)
		{
		FakeMatrix2x2 result;
		Divide(left, right, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param value
	 * @param result
	 */
	static void Negate(const FakeMatrix2x2 &value, FakeMatrix2x2 &result)
		{
		result.M11 = -value.M11;
		result.M12 = -value.M12;
		result.M21 = -value.M21;
		result.M22 = -value.M22;
		}

	/**
	 * 
	 * .
	 * 
	 * @param value
	 * @return 
	 */
	static FakeMatrix2x2 Negate(const FakeMatrix2x2 &value)
		{
		FakeMatrix2x2 result;
		Negate(value, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	FakeMatrix2x2 operator+(const FakeMatrix2x2 &other) const
		{
		FakeMatrix2x2 result;
		Add(*this, other, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	FakeMatrix2x2 operator-(const FakeMatrix2x2 &other) const
		{
		FakeMatrix2x2 result;
		Subtract(*this, other, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	FakeMatrix2x2 operator*(const FakeMatrix2x2 &other) const
		{
		FakeMatrix2x2 result;
		Multiply(*this, other, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param scalar
	 * @return 
	 */
	FakeMatrix2x2 operator*(T scalar) const
		{
		FakeMatrix2x2 result;
		Multiply(*this, scalar, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	FakeMatrix2x2 operator/(const FakeMatrix2x2 &other) const
		{
		FakeMatrix2x2 result;
		Divide(*this, other, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param scalar
	 * @return 
	 */
	FakeMatrix2x2 operator/(T scalar) const
		{
		FakeMatrix2x2 result;
		Divide(*this, scalar, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	FakeMatrix2x2 &operator+=(const FakeMatrix2x2 &other)
		{
		Add(*this, other, *this);
		return *this;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	FakeMatrix2x2 &operator-=(const FakeMatrix2x2 &other)
		{
		Subtract(*this, other, *this);
		return *this;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	FakeMatrix2x2 &operator*=(const FakeMatrix2x2 &other)
		{
		Multiply(*this, other, *this);
		return *this;
		}

	/**
	 * 
	 * .
	 * 
	 * @param scalar
	 * @return 
	 */
	FakeMatrix2x2 &operator*=(T scalar)
		{
		Multiply(*this, scalar, *this);
		return *this;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	FakeMatrix2x2 &operator/=(const FakeMatrix2x2 &other)
		{
		Divide(*this, other, *this);
		return *this;
		}

	/**
	 * 
	 * .
	 * 
	 * @param scalar
	 * @return 
	 */
	FakeMatrix2x2 &operator/=(T scalar)
		{
		Divide(*this, scalar, *this);
		return *this;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	bool operator==(const FakeMatrix2x2 &other) const
		{
		return
			fake_near_equal(M11, other.M11) &&
			fake_near_equal(M12, other.M12) &&
			fake_near_equal(M21, other.M21) &&
			fake_near_equal(M22, other.M22);
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	bool operator!=(const FakeMatrix2x2 &other) const
		{
		return !(*this == other);
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	bool operator<(const FakeMatrix2x2 &other) const
		{
		return
			M11 < other.M11 &&
			M12 < other.M12 &&
			M21 < other.M21 &&
			M22 < other.M22;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	bool operator<=(const FakeMatrix2x2 &other) const
		{
		return
			M11 <= other.M11 &&
			M12 <= other.M12 &&
			M21 <= other.M21 &&
			M22 <= other.M22;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	bool operator>(const FakeMatrix2x2 &other) const
		{
		return
			M11 > other.M11 &&
			M12 > other.M12 &&
			M21 > other.M21 &&
			M22 > other.M22;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	bool operator>=(const FakeMatrix2x2 &other) const
		{
		return
			M11 >= other.M11 &&
			M12 >= other.M12 &&
			M21 >= other.M21 &&
			M22 >= other.M22;
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

		for (uint32 i = 0; i < 4; ++i)
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

		for (uint32 i = 0; i < 4; ++i)
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
		stream << matrix.M11 << ", " << matrix.M12 << ",\n";
		stream << matrix.M21 << ", " << matrix.M22;
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

