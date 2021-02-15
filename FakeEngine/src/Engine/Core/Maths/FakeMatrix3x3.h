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
#include "Engine/Core/Maths/FakeVector2.h"
#include "Engine/Core/Maths/FakeVector3.h"
#include "Engine/Core/Maths/FakeVector4.h"

template<typename T>
struct FakeQuaternion;

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

	/**
	 * 
	 * constructor.
	 * 
	 */
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

	/**
	 * 
	 * constructor.
	 * 
	 * @param value The Value to initialize the diagonal with.
	 */
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

	/**
	 * 
	 * constructor.
	 * 
	 * @param m11
	 * @param m12
	 * @param m13
	 * @param m21
	 * @param m22
	 * @param m23
	 * @param m31
	 * @param m32
	 * @param m33
	 */
	FakeMatrix3x3(T m11, T m12, T m13, T m21, T m22, T m23, T m31, T m32, T m33)
		: M11(m11), M12(m12), M13(m13), M21(m21), M22(m22), M23(m23), M31(m31), M32(m32), M33(m33)
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param values
	 */
	FakeMatrix3x3(T values[9])
		{
		memcpy(Raw, values, 9 * sizeof(T));
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param values
	 */
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
	FakeMatrix3x3(const FakeMatrix3x3 &other)
		{
		for (uint32 i = 0; i < 9; ++i)
			Raw[i] = other.Raw[i];
		}

	/**
	 * 
	 * copy operator.
	 * 
	 * @param The matrix to copy.
	 * @return Returns the copied instance.
	 */
	FakeMatrix3x3 &operator=(const FakeMatrix3x3 &other)
		{
		for (uint32 i = 0; i < 9; ++i)
			Raw[i] = other.Raw[i];

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
		result << M11 << ", " << M12 << ", " << M13 << ",\n";
		result << M21 << ", " << M22 << ", " << M23 << ",\n";
		result << M31 << ", " << M32 << ", " << M33 << "\n";
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param values
	 * @param index
	 */
	void SetRow(const FakeVector3<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			M11 = values.X;
			M12 = values.Y;
			M13 = values.Z;
			}
		else if (index == 1)
			{
			M21 = values.X;
			M22 = values.Y;
			M23 = values.Z;
			}
		else if (index == 2)
			{
			M31 = values.X;
			M32 = values.Y;
			M33 = values.Z;
			}
		}

	/**
	 * 
	 * .
	 * 
	 * @param index
	 * @return 
	 */
	FakeVector3<T> GetRow(uint32 index = 0) const
		{
		if (index == 0)
			{
			return FakeVector3<T>(M11, M12, M13);
			}
		else if (index == 1)
			{
			return FakeVector3<T>(M21, M22, M23);
			}
		else if (index == 2)
			{
			return FakeVector3<T>(M31, M32, M33);
			}

		return FakeVector3<T>::Zero;
		}

	/**
	 * 
	 * .
	 * 
	 * @param values
	 * @param index
	 */
	void SetColumn(const FakeVector3<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			M11 = values.X;
			M21 = values.Y;
			M31 = values.Z;
			}
		else if (index == 1)
			{
			M12 = values.X;
			M22 = values.Y;
			M32 = values.Z;
			}
		else if (index == 2)
			{
			M13 = values.X;
			M23 = values.Y;
			M33 = values.Z;
			}
		}

	/**
	 * 
	 * .
	 * 
	 * @param index
	 * @return 
	 */
	FakeVector3<T> GetColumn(uint32 index = 0) const
		{
		if (index == 0)
			{
			return FakeVector3<T>(M11, M21, M31);
			}
		else if (index == 1)
			{
			return FakeVector3<T>(M12, M22, M32);
			}
		else if (index == 2)
			{
			return FakeVector3<T>(M13, M23, M33);
			}

		return FakeVector3<T>::Zero;
		}

	/**
	 * 
	 * .
	 * 
	 * @return 
	 */
	FakeVector3<T> GetScaleVector() const
		{
		return FakeVector3<T>(M11, M22, M33);
		}

	/**
	 * 
	 * .
	 * 
	 * @param values
	 */
	void SetScaleVector(const FakeVector3<T> &values)
		{
		M11 = values.X;
		M22 = values.Y;
		M33 = values.Z;
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
		return M11 * M22 * M33 + M12 * M23 * M31 + M13 * M21 * M32 - M13 * M22 * M31 - M12 * M21 * M33 - M11 * M23 * M32;
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
	static void Inverse(const FakeMatrix3x3 &value, FakeMatrix3x3 &result)
		{
		const T d11 = value.M22 * value.M33 + value.M23 * -value.M32;
		const T d12 = value.M21 * value.M33 + value.M23 * -value.M31;
		const T d13 = value.M21 * value.M32 + value.M22 * -value.M31;

		T det = value.M11 * d11 - value.M12 * d12 + value.M13 * d13;
		if (FAKE_ABS(det) < FAKE_ZERO_TOLERANCE)
			{
			result = Zero;
			return;
			}

		det = static_cast<T>(1) / det;

		const T d21 = value.M12 * value.M33 + value.M13 * -value.M32;
		const T d22 = value.M11 * value.M33 + value.M13 * -value.M31;
		const T d23 = value.M11 * value.M32 + value.M12 * -value.M31;

		const T d31 = value.M12 * value.M23 - value.M13 * value.M22;
		const T d32 = value.M11 * value.M23 - value.M13 * value.M21;
		const T d33 = value.M11 * value.M22 - value.M12 * value.M21;

		result.M11 = +d11 * det;
		result.M12 = -d21 * det;
		result.M13 = +d31 * det;

		result.M21 = -d12 * det;
		result.M22 = +d22 * det;
		result.M23 = -d32 * det;
		
		result.M31 = +d13 * det;
		result.M32 = -d23 * det;
		result.M33 = +d33 * det;
		}

	/**
	 * 
	 * .
	 * 
	 * @param value
	 * @return 
	 */
	static FakeMatrix3x3 Inverse(const FakeMatrix3x3 &value)
		{
		FakeMatrix3x3 result;
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
	static void Transpose(const FakeMatrix3x3 &value, FakeMatrix3x3 &result)
		{
		result.M11 = value.M11;
		result.M12 = value.M21;
		result.M13 = value.M31;

		result.M21 = value.M12;
		result.M22 = value.M22;
		result.M23 = value.M32;
		
		result.M31 = value.M13;
		result.M32 = value.M23;
		result.M33 = value.M33;
		}

	/**
	 * 
	 * .
	 * 
	 * @param value
	 * @return 
	 */
	static FakeMatrix3x3 Transpose(const FakeMatrix3x3 &value)
		{
		FakeMatrix3x3 result;
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
	static void Add(const FakeMatrix3x3 &left, const FakeMatrix3x3 &right, FakeMatrix3x3 &result)
		{
		result.M11 = left.M11 + right.M11;
		result.M12 = left.M12 + right.M12;
		result.M13 = left.M13 + right.M13;
		result.M21 = left.M21 + right.M21;
		result.M22 = left.M22 + right.M22;
		result.M23 = left.M23 + right.M23;
		result.M31 = left.M31 + right.M31;
		result.M32 = left.M32 + right.M32;
		result.M33 = left.M33 + right.M33;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix3x3 Add(const FakeMatrix3x3 &left, const FakeMatrix3x3 &right)
		{
		FakeMatrix3x3 result;
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
	static void Subtract(const FakeMatrix3x3 &left, const FakeMatrix3x3 &right, FakeMatrix3x3 &result)
		{
		result.M11 = left.M11 - right.M11;
		result.M12 = left.M12 - right.M12;
		result.M13 = left.M13 - right.M13;
		result.M21 = left.M21 - right.M21;
		result.M22 = left.M22 - right.M22;
		result.M23 = left.M23 - right.M23;
		result.M31 = left.M31 - right.M31;
		result.M32 = left.M32 - right.M32;
		result.M33 = left.M33 - right.M33;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix3x3 Subtract(const FakeMatrix3x3 &left, const FakeMatrix3x3 &right)
		{
		FakeMatrix3x3 result;
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
	static void Multiply(const FakeMatrix3x3 &left, const FakeMatrix3x3 &right, FakeMatrix3x3 &result)
		{
		result.M11 = left.M11 *right.M11 + left.M12 * right.M21 + left.M13 * right.M31;
		result.M12 = left.M11 *right.M12 + left.M12 * right.M22 + left.M13 * right.M32;
		result.M13 = left.M11 *right.M13 + left.M12 * right.M23 + left.M13 * right.M33;
		result.M21 = left.M21 *right.M11 + left.M22 * right.M21 + left.M23 * right.M31;
		result.M22 = left.M21 *right.M12 + left.M22 * right.M22 + left.M23 * right.M32;
		result.M23 = left.M21 *right.M13 + left.M22 * right.M23 + left.M23 * right.M33;
		result.M31 = left.M31 *right.M11 + left.M32 * right.M21 + left.M33 * right.M31;
		result.M32 = left.M31 *right.M12 + left.M32 * right.M22 + left.M33 * right.M32;
		result.M33 = left.M31 *right.M13 + left.M32 * right.M23 + left.M33 * right.M33;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix3x3 Multiply(const FakeMatrix3x3 &left, const FakeMatrix3x3 &right)
		{
		FakeMatrix3x3 result;
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
	static void Multiply(const FakeMatrix3x3 &left, T right, FakeMatrix3x3 &result)
		{
		result.M11 = left.M11 * right;
		result.M12 = left.M12 * right;
		result.M13 = left.M13 * right;
		result.M21 = left.M21 * right;
		result.M22 = left.M22 * right;
		result.M23 = left.M23 * right;
		result.M31 = left.M31 * right;
		result.M32 = left.M32 * right;
		result.M33 = left.M33 * right;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix3x3 Multiply(const FakeMatrix3x3 &left, T right)
		{
		FakeMatrix3x3 result;
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
	static void Divide(const FakeMatrix3x3 &left, const FakeMatrix3x3 &right, FakeMatrix3x3 &result)
		{
		result.M11 = left.M11 / right.M11;
		result.M12 = left.M12 / right.M12;
		result.M13 = left.M13 / right.M13;
		result.M21 = left.M21 / right.M21;
		result.M22 = left.M22 / right.M22;
		result.M23 = left.M23 / right.M23;
		result.M31 = left.M31 / right.M31;
		result.M32 = left.M32 / right.M32;
		result.M33 = left.M33 / right.M33;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix3x3 Divide(const FakeMatrix3x3 &left, const FakeMatrix3x3 &right)
		{
		FakeMatrix3x3 result;
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
	static void Divide(const FakeMatrix3x3 &left, T right, FakeMatrix3x3 &result)
		{
		FAKE_ASSERT(!fake_is_zero(right));
		const T inv = static_cast<T>(1) / right;

		result.M11 = left.M11 * inv;
		result.M12 = left.M12 * inv;
		result.M13 = left.M13 * inv;
		result.M21 = left.M21 * inv;
		result.M22 = left.M22 * inv;
		result.M23 = left.M23 * inv;
		result.M31 = left.M31 * inv;
		result.M32 = left.M32 * inv;
		result.M33 = left.M33 * inv;
		}

	/**
	 * 
	 * .
	 * 
	 * @param left
	 * @param right
	 * @return 
	 */
	static FakeMatrix3x3 Divide(const FakeMatrix3x3 &left, T right)
		{
		FakeMatrix3x3 result;
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
	static void Negate(const FakeMatrix3x3 &value, FakeMatrix3x3 &result)
		{
		result.M11 = value.M11;
		result.M12 = value.M12;
		result.M13 = value.M13;
		result.M21 = value.M21;
		result.M22 = value.M22;
		result.M23 = value.M23;
		result.M31 = value.M31;
		result.M32 = value.M32;
		result.M33 = value.M33;
		}

	/**
	 * 
	 * .
	 * 
	 * @param value
	 * @return 
	 */
	static FakeMatrix3x3 Negate(const FakeMatrix3x3 &value)
		{
		FakeMatrix3x3 result;
		Negate(value, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param translation
	 * @param result
	 */
	static void Translate2D(const FakeVector2<T> &translation, FakeMatrix3x3 &result)
		{
		result = FakeMatrix3x3(
			static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
			static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
			translation.X, translation.Y, static_cast<T>(1)
		);
		}

	/**
	 * 
	 * .
	 * 
	 * @param translation
	 * @return 
	 */
	static FakeMatrix3x3 Translate2D(const FakeVector2<T> &translation)
		{
		FakeMatrix3x3 result;
		Translate2D(translation, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param point
	 * @param transform
	 * @param result
	 */
	static void TransformPoint(const FakeVector2<T> &point, const FakeMatrix3x3 &transform, FakeVector2<T> &result)
		{
		result.X = point.X * transform.M11 + point.Y * transform.M21 + transform.M31;
		result.Y = point.X * transform.M12 + point.Y * transform.M22 + transform.M32;
		}

	/**
	 * 
	 * .
	 * 
	 * @param vector
	 * @param transform
	 * @param result
	 */
	static void TransformVector(const FakeVector2<T> &vector, const FakeMatrix3x3 &transform, FakeVector2<T> &result)
		{
		result.X = vector.X * transform.M11 + vector.Y * transform.M21;
		result.Y = vector.X * transform.M12 + vector.Y * transform.M22;
		}

	/**
	 * 
	 * .
	 * 
	 * @param rotation
	 * @param result
	 */
	static void Rotate(const FakeQuaternion<T> &rotation, FakeMatrix3x3 &result)
		{
		const T xx = rotation.X * rotation.X;
		const T yy = rotation.Y * rotation.Y;
		const T zz = rotation.Z * rotation.Z;
		const T xy = rotation.X * rotation.Y;
		const T zw = rotation.Z * rotation.W;
		const T zx = rotation.Z * rotation.X;
		const T yw = rotation.Y * rotation.W;
		const T yz = rotation.Y * rotation.Z;
		const T xw = rotation.X * rotation.W;

		result.M11 = static_cast<T>(1) - static_cast<T>(2) * (yy + zz);
		result.M12 = static_cast<T>(2) * (xy + zw);
		result.M13 = static_cast<T>(2) * (zx - yw);

		result.M21 = static_cast<T>(2) * (xy - zw);
		result.M22 = static_cast<T>(1) - static_cast<T>(2) * (zz + xx);
		result.M23 = static_cast<T>(2) * (yz + xw);

		result.M31 = static_cast<T>(2) * (zx + yw);
		result.M32 = static_cast<T>(2) * (yz - xw);
		result.M33 = static_cast<T>(1) - static_cast<T>(2) * (yy + xx);
		}

	/**
	 * 
	 * .
	 * 
	 * @param rotation
	 * @return 
	 */
	static FakeMatrix3x3 Rotate(const FakeQuaternion<T> &rotation)
		{
		FakeMatrix3x3 result;
		Rotate(rotation, result);
		return result;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	FakeMatrix3x3 operator+(const FakeMatrix3x3 &other) const
		{
		FakeMatrix3x3 result;
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
	FakeMatrix3x3 operator-(const FakeMatrix3x3 &other) const
		{
		FakeMatrix3x3 result;
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
	FakeMatrix3x3 operator*(const FakeMatrix3x3 &other) const
		{
		FakeMatrix3x3 result;
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
	FakeMatrix3x3 operator*(T scalar) const
		{
		FakeMatrix3x3 result;
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
	FakeMatrix3x3 operator/(const FakeMatrix3x3 &other) const
		{
		FakeMatrix3x3 result;
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
	FakeMatrix3x3 operator/(T scalar) const
		{
		FakeMatrix3x3 result;
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
	FakeMatrix3x3 &operator+=(const FakeMatrix3x3 &other)
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
	FakeMatrix3x3 &operator-=(const FakeMatrix3x3 &other)
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
	FakeMatrix3x3 &operator*=(const FakeMatrix3x3 &other)
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
	FakeMatrix3x3 &operator*=(T scalar)
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
	FakeMatrix3x3 &operator/=(const FakeMatrix3x3 &other)
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
	FakeMatrix3x3 &operator/=(T scalar)
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
	bool operator==(const FakeMatrix3x3 &other) const
		{
		return
			fake_near_equal(M11, other.M11) &&
			fake_near_equal(M12, other.M12) &&
			fake_near_equal(M13, other.M13) &&
			fake_near_equal(M21, other.M21) &&
			fake_near_equal(M22, other.M22) &&
			fake_near_equal(M23, other.M23) &&
			fake_near_equal(M31, other.M31) &&
			fake_near_equal(M32, other.M32) &&
			fake_near_equal(M33, other.M33);
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	bool operator!=(const FakeMatrix3x3 &other) const
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
	bool operator<(const FakeMatrix3x3 &other) const
		{
		return
			M11 < other.M11 &&
			M12 < other.M12 &&
			M13 < other.M13 &&
			M21 < other.M21 &&
			M22 < other.M22 &&
			M23 < other.M23 &&
			M31 < other.M31 &&
			M32 < other.M32 &&
			M33 < other.M33;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	bool operator<=(const FakeMatrix3x3 &other) const
		{
		return
			M11 <= other.M11 &&
			M12 <= other.M12 &&
			M13 <= other.M13 &&
			M21 <= other.M21 &&
			M22 <= other.M22 &&
			M23 <= other.M23 &&
			M31 <= other.M31 &&
			M32 <= other.M32 &&
			M33 <= other.M33;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	bool operator>(const FakeMatrix3x3 &other) const
		{
		return
			M11 > other.M11 &&
			M12 > other.M12 &&
			M13 > other.M13 &&
			M21 > other.M21 &&
			M22 > other.M22 &&
			M23 > other.M23 &&
			M31 > other.M31 &&
			M32 > other.M32 &&
			M33 > other.M33;
		}

	/**
	 * 
	 * .
	 * 
	 * @param other
	 * @return 
	 */
	bool operator>=(const FakeMatrix3x3 &other) const
		{
		return
			M11 >= other.M11 &&
			M12 >= other.M12 &&
			M13 >= other.M13 &&
			M21 >= other.M21 &&
			M22 >= other.M22 &&
			M23 >= other.M23 &&
			M31 >= other.M31 &&
			M32 >= other.M32 &&
			M33 >= other.M33;
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

		for (uint32 i = 0; i < 9; ++i)
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

		for (uint32 i = 0; i < 9; ++i)
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
		stream << matrix.M11 << ", " << matrix.M12 << ", " << matrix.M13 << ",\n";
		stream << matrix.M21 << ", " << matrix.M22 << ", " << matrix.M23 << ",\n";
		stream << matrix.M31 << ", " << matrix.M32 << ", " << matrix.M33;
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
