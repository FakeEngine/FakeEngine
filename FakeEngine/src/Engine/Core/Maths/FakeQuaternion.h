/*****************************************************************
 * \file   FakeQuaternion.h
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
#include "Engine/Core/Maths/FakeMatrix4x4.h"

/**
 * 
 * Represents a four dimensional mathematical quaternion. Euler angles are stored in: pitch, yaw, roll order (x, y, z).
 * 
 */
template<typename T>
struct FAKE_API FakeQuaternion
	{

	union
		{
		struct
			{
			/**
			 * 
			 * The X component.
			 * 
			 */
			T X;

			/**
			 * 
			 * The Y component.
			 * 
			 */
			T Y;

			/**
			 * 
			 * The Z component.
			 * 
			 */
			T Z;

			/**
			 * 
			 * The W component.
			 * 
			 */
			T W;
			};

		T Raw[4];
		};

	// Quaternion with all components equal 0.
	static FakeQuaternion Zero;

	// Quaternion with all components equal 1.
	static FakeQuaternion One;

	// Identity quaternion (represents no rotation).
	static FakeQuaternion Identity;

	/**
	 * 
	 * empty constructor.
	 * 
	 */
	FakeQuaternion()
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param xyzw The value to set
	 */
	FakeQuaternion(const T xyzw)
		: X(xyzw), Y(xyzw), Z(xyzw), W(xyzw)
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param x The X component to set.
	 * @param y The Y component to set.
	 * @param z The Z component to set.
	 * @param w The W component to set.
	 */
	FakeQuaternion(const T x, const T y, const T z, const T w)
		: X(x), Y(y), Z(z), W(w)
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param eulerAngles The euler angles to convert into a quaternion
	 */
	FakeQuaternion(const FakeVector3<T> &eulerAngles)
		{
		FakeVector3<T> c = { fake_cos(eulerAngles.X * static_cast<T>(0.5)), fake_cos(eulerAngles.Y * static_cast<T>(0.5)), fake_cos(eulerAngles.Z * static_cast<T>(0.5)) };
		FakeVector3<T> s = { fake_sin(eulerAngles.X * static_cast<T>(0.5)), fake_sin(eulerAngles.Y * static_cast<T>(0.5)), fake_sin(eulerAngles.Z * static_cast<T>(0.5)) };

		W = c.X * c.Y * c.Z + s.X * s.Y * s.Z;
		X = s.X * c.Y * c.Z - c.X * s.Y * s.Z;
		Y = c.X * s.Y * c.Z + s.X * c.Y * s.Z;
		Z = c.X * c.Y * s.Z - s.X * s.Y * c.Z;
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param v The components to set.
	 */
	FakeQuaternion(const FakeVector4<T> &v)
		: X(v.X), Y(v.Y), Z(v.Z), W(v.W)
		{
		}

	/**
	 * 
	 * copy constructor.
	 * 
	 * @param other The instance to copy.
	 */
	FakeQuaternion(const FakeQuaternion &other)
		: X(other.X), Y(other.Y), Z(other.Z), W(other.W)
		{
		}

	/**
	 * 
	 * Converts the quaternion to a String.
	 * 
	 * @return Returns the Quaternion as a String.
	 */
	FakeString ToString() const
		{
		return "Quaternion(" + FakeString::ToString(X) + ", " + FakeString::ToString(Y) + ", " + FakeString::ToString(Z) + ", " + FakeString::ToString(W) + ")";
		}

	static FakeMatrix3x3<T> ToMatrix3(const FakeQuaternion &other)
		{
		FakeMatrix3x3<T> result = FakeMatrix3x3<T>::Identity;
		T qxx(other.X * other.X);
		T qyy(other.Y * other.Y);
		T qzz(other.Z * other.Z);
		T qxz(other.X * other.Z);
		T qxy(other.X * other.Y);
		T qyz(other.Y * other.Z);
		T qwx(other.W * other.X);
		T qwy(other.W * other.Y);
		T qwz(other.W * other.Z);

		result[0 + 0 * 3] = static_cast<T>(1) - static_cast<T>(2) * (qyy + qzz);
		result[0 + 1 * 3] = static_cast<T>(2) * (qxy + qwz);
		result[0 + 2 * 3] = static_cast<T>(2) * (qxz - qwy);

		result[1 + 0 * 3] = static_cast<T>(2) * (qxy - qwz);
		result[1 + 1 * 3] = static_cast<T>(1) - static_cast<T>(2) * (qxx + qzz);
		result[1 + 2 * 3] = static_cast<T>(2) * (qyz + qwx);

		result[2 + 0 * 3] = static_cast<T>(2) * (qxz + qwy);
		result[2 + 1 * 3] = static_cast<T>(2) * (qyz - qwx);
		result[2 + 2 * 3] = static_cast<T>(1) - static_cast<T>(2) * (qxx + qyy);
		return result;
		}

	static FakeMatrix4x4<T> ToMatrix4(const FakeQuaternion &other)
		{
		return FakeMatrix4x4<T>(ToMatrix3(other));
		}

	/**
	 * 
	 * Gets a value indicating whether this instance is equivalent to the identity quaternion.
	 * 
	 * @return Returns true if the current instance is the identity quaternion.
	 */
	bool IsIdentity() const
		{
		return fake_is_zero(X) && fake_is_zero(Y) && fake_is_zero(Z) && fake_is_zero(W);
		}

	/**
	 * 
	 * Gets a value indicting whether this instance is normalized.
	 * 
	 * @return Returns true if is normalized, otherwise false.
	 */
	bool IsNormalized() const
		{
		return fake_is_one(X * X + Y * Y + Z * Z + W * W);
		}

	/**
	 * 
	 * Returns true if quaternion has one or more components which are not a number.
	 * 
	 * @return Returns true if one or more components are NaN.
	 */
	bool IsNaN() const
		{
		return isnan(X) || isnan(Y) || isnan(Z) || isnan(W);
		}

	/**
	 * 
	 * Returns true if quaternion has one or more components equal to +/- infinity.
	 * 
	 * @return Returns true if one or more components are equal to +/- infinity.
	 */
	bool IsInfinity() const
		{
		return isinf(X) || isinf(Y) || isinf(Z) || isinf(W);
		}

	/**
	 * 
	 * Returns true if quaternion has one or more components equal to +/- infinity or NaN.
	 * 
	 * @return Returns true if one or more components are equal to +/- infinity or NaN.
	 */
	bool IsNanOrInfinity() const
		{
		return IsNaN() || IsInfinity();
		}

	/**
	 * 
	 * Calculates the length of the quaternion.
	 * 
	 * @return Returns the length of the quaternion.
	 */
	T Length() const
		{
		return fake_sqrt(X * X + Y * Y + Z * Z + W * W);
		}

	/**
	 * 
	 * Calculates the squared length of the quaternion.
	 * 
	 * @return Returns the squared length of the quaternion.
	 */
	T LengthSquared() const
		{
		return X * X + Y * Y + Z * Z + W * W;
		}

	/**
	 * 
	 * Gets the angle of the quaternion.
	 * 
	 * @return Returns the angle.
	 */
	T GetAngle() const
		{
		const T length = X * X + Y * Y + Z * Z;
		if (fake_is_zero(length))
			return static_cast<T>(0);

		return static_cast<T>(2) * acosf(fake_clamp(W, static_cast<T>(-1), static_cast<T>(1)));
		}

	/**
	 * 
	 * Gets the axis components of the quaternion.
	 * 
	 * @return Returns the axis.
	 */
	FakeVector3<T> GetAxis() const
		{
		const T length = X * X + Y * Y + Z * Z;
		if (fake_is_zero(length))
			return FakeVector3<T>::UnitX;

		const T inv = static_cast<T>(1) / fake_sqrt(length);
		return FakeVector3<T>(X * inv, Y * inv, Z * inv);
		}

	/**
	 * 
	 * Gets the euler angle (pitch, yaw, roll) in degrees.
	 * 
	 * @return Returns The euler angle.
	 */
	FakeVector3<T> GetEuler() const
		{
		FakeVector3<T> result;
		const T sqw = W * W;
		const T sqx = X * X;
		const T sqy = Y * Y;
		const T sqz = Z * Z;
		const T unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
		const T test = X * W - Y * Z;

		if (test > static_cast<T>(0.499995) * unit)
			{
			// singularity at north pole

			// yaw pitch roll
			result.Y = static_cast<T>(2) * fake_atan2(Y, X);
			result.X = FAKE_PI_OVER_2;
			result.Z = static_cast<T>(0);
			}
		else if (test < static_cast<T>(-0.499995) * unit)
			{
			// singularity at south pole

			// yaw pitch roll
			result.Y = static_cast<T>(-2) * fake_atan2(Y, X);
			result.X = -FAKE_PI_OVER_2;
			result.Z = static_cast<T>(0);
			}
		else
			{
			// yaw pitch roll
			const FakeQuaternion q = FakeQuaternion(W, Z, X, Y);
			result.Y = fake_atan2(static_cast<T>(2) * q.X * q.W + static_cast<T>(2) * q.Y * q.Z, static_cast<T>(1) - static_cast<T>(2) * (q.Z * q.Z + q.W * q.W));
			result.X = fake_asin(static_cast<T>(2) * (q.X * q.Z - q.W * q.Y));
			result.Z = fake_atan2(static_cast<T>(2) * q.X * q.Y + static_cast<T>(2) * q.Z * q.W, static_cast<T>(1) - static_cast<T>(2) * (q.Y * q.Y + q.Z * q.Z));
			}

		result *= (static_cast<T>(180) / FAKE_PI);
		result.UnwindEuler();
		return result;
		}

	/**
	 * 
	 * Conjugates the quaternion.
	 * 
	 */
	void Conjugate()
		{
		X = -X;
		Y = -Y;
		Z = -Z;
		}

	/**
	 * 
	 * Gets the conjugated quaternion.
	 * 
	 * @return Returns the conjugated quaternion.
	 */
	FakeQuaternion Conjugated() const
		{
		return { -X, -Y, -Z, W };
		}

	/**
	 * 
	 * Conjugates and renormalizes the quaternion.
	 * 
	 */
	void Invert()
		{
		T lengthSq = LengthSquared();
		if (!fake_is_zero(lengthSq))
			{
			lengthSq = static_cast<T>(1) / lengthSq;
			X = -X * lengthSq;
			Y = -Y * lengthSq;
			Z = -Z * lengthSq;
			W =  W * lengthSq;
			}
		}

	/**
	 * 
	 * Reverses the direction of the quaternion.
	 * 
	 */
	void Negate()
		{
		X = -X;
		Y = -Y;
		Z = -Z;
		W = -W;
		}

	/**
	 * 
	 * Converts the quaternion into a unit quaternion.
	 * 
	 */
	void Normalize()
		{
		const T length = Length();
		if (!fake_is_zero(length))
			{
			const T inv = static_cast<T>(1) / length;
			X *= inv;
			Y *= inv;
			Z *= inv;
			W *= inv;
			}
		}

	/**
	 *
	 * Determines whether the specified quaternions are equal.
	 *
	 * @param a The first quaternion to compare.
	 * @param b The second quaternion to compare.
	 * @return Returns true if the specified quaternions are equal - otherwise false.
	 */
	static bool NearEqual(const FakeQuaternion &a, const FakeQuaternion &b)
		{
		return Dot(a, b) > static_cast<T>(0.99999999);
		}

	/**
	 *
	 * Determines whether the specified quaternions are equal.
	 *
	 * @param a The first quaternion to compare.
	 * @param b The second quaternion to compare.
	 * @param epsilon The comparision threshold value.
	 * @return Returns true if the specified quaternions are equal - otherwise false.
	 */
	static bool NearEqual(const FakeQuaternion &a, const FakeQuaternion &b, T epsilon)
		{
		return Dot(a, b) > static_cast<T>(1) - epsilon;
		}

	/**
	 * 
	 * Scales a quaternion by the given value.
	 * 
	 * @param scale The amount by which to scale the quaternion.
	 */
	void Multiply(T scale)
		{
		X *= scale;
		Y *= scale;
		Z *= scale;
		W *= scale;
		}

	/**
	 * 
	 * Multiplies a quaternion with another instance.
	 * 
	 * @param other The other quaternion to multiply the current instance with.
	 */
	void Multiply(const FakeQuaternion &other)
		{
		const T a = Y * other.Z - Z * other.Y;
		const T b = Z * other.X - X * other.Z;
		const T c = X * other.Y - Y * other.X;
		const T d = X * other.X + Y * other.Y + Z * other.Z;

		X = X * other.W + other.X * W + a;
		Y = Y * other.W + other.Y * W + b;
		Z = Z * other.W + other.Z * W + c;
		W = W * other.W - d;
		}

	/**
	 * 
	 * Calculates the dot product of two quaternions.
	 * 
	 * @param left The first source quaternion.
	 * @param right The second source quaternion.
	 * @return Returns the dot product of the two quaternions.
	 */
	static T Dot(const FakeQuaternion &left, const FakeQuaternion &right)
		{
		return left.X * right.X + left.Y * right.Y + left.Z * right.Z + left.W * right.W;
		}

	/**
	 * 
	 * Calculates the angle between two quaternions.
	 * 
	 * @param a The first source quaternion.
	 * @param b The second source quaternion.
	 * @return Returns the angle in degrees between two quaternions a and b.
	 */
	static T AngleBetween(const FakeQuaternion &a, const FakeQuaternion &b)
		{
		const T dot = Dot(a, b);
		return dot > static_cast<T>(0.99999999) ? 0 : fake_acos(fake_min(FAKE_ABS(dot), static_cast<T>(1))) * static_cast<T>(2) * static_cast<T>(57.29578);
		}

	/**
	 * 
	 * Adds two quaternions.
	 * 
	 * @param left The first quaternion to add.
	 * @param right The second quaternion to add.
	 * @param result The result where the addition should be stored in.
	 */
	static void Add(const FakeQuaternion &left, const FakeQuaternion &right, FakeQuaternion &result)
		{
		result.X = left.X + right.X;
		result.Y = left.Y + right.Y;
		result.Z = left.Z + right.Z;
		result.W = left.W + right.W;
		}

	/**
	 * 
	 * Subtracts two quaternions.
	 * 
	 * @param left The first quaternion to subtract.
	 * @param right The second quaternion to subtract.
	 * @param result The result where the subtraction should be stored in.
	 */
	static void Subtract(const FakeQuaternion &left, const FakeQuaternion &right, FakeQuaternion &result)
		{
		result.X = left.X - right.X;
		result.Y = left.Y - right.Y;
		result.Z = left.Z - right.Z;
		result.W = left.W - right.W;
		}

	/**
	 * 
	 * Multiplies a quaternion with another.
	 * 
	 * @param left The first quaternion to multiply.
	 * @param right The second quaternion to multiply.
	 * @param result The result where the multiplication should be stored in.
	 */
	static void Multiply(const FakeQuaternion &left, const FakeQuaternion &right, FakeQuaternion &result)
		{
		const T a = left.Y * right.Z - left.Z * right.Y;
		const T b = left.Z * right.X - left.X * right.Z;
		const T c = left.X * right.Y - left.Y * right.X;
		const T d = left.X * right.X + left.Y * right.Y + left.Z * right.Z;

		result.X = left.X * right.W + right.X * left.W + a;
		result.Y = left.Y * right.W + right.Y * left.W + b;
		result.Z = left.Z * right.W + right.Z * left.W + c;
		result.W = left.W * right.W - d;
		}

	/**
	 * 
	 * Scales a quaternion by a given value.
	 * 
	 * @param value The quaternion to scale.
	 * @param scale The amount by which the quaternion should be scaled.
	 * @param result The result where the scaled quaternion should be stored in.
	 */
	static void Multiply(const FakeQuaternion &value, T scale, FakeQuaternion &result)
		{
		result.X = value.X * scale;
		result.Y = value.Y * scale;
		result.Z = value.Z * scale;
		result.W = value.W * scale;
		}

	/**
	 * 
	 * Calculates the inverse of the specified quaternion.
	 * 
	 * @param value The quaternion whose inverse is to be calculated.
	 * @param result The result where the inversion of the specified quaternion is stored in.
	 */
	static void Invert(const FakeQuaternion &value, FakeQuaternion &result)
		{
		result = value;
		result.Invert();
		}

	/**
	 * 
	 * Calculates the inverse of the specified quaternion.
	 * 
	 * @param value The quaternion whose inverse is to be calculated.
	 * @return Returns the inverse of the specified quaternion.
	 */
	static FakeQuaternion Invert(const FakeQuaternion &value)
		{
		FakeQuaternion result;
		Invert(value, result);
		return result;
		}

	/**
	 * 
	 * Reverses the direction of a given quaternion.
	 * 
	 * @param value The quaternion to negate.
	 * @param result The result where the negated quaternion is stored in.
	 */
	static void Negate(const FakeQuaternion &value, FakeQuaternion &result)
		{
		result.X = -value.X;
		result.Y = -value.Y;
		result.Z = -value.Z;
		result.W = -value.W;
		}

	/**
	 * 
	 * Performs a linear interpolation between two quaternions.
	 * 
	 * @param start The start quaternion.
	 * @param end The end quaternion.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @param result The result where the interpolated quaternion is stored in.
	 */
	static void Lerp(const FakeQuaternion &start, const FakeQuaternion &end, T amount, FakeQuaternion &result)
		{
		const T inverse = static_cast<T>(1) - amount;
		if (Dot(start, end) >= static_cast<T>(0))
			{
			result.X = inverse * start.X + amount * end.X;
			result.Y = inverse * start.Y + amount * end.Y;
			result.Z = inverse * start.Z + amount * end.Z;
			result.W = inverse * start.W + amount * end.W;
			}
		else
			{
			result.X = inverse * start.X - amount * end.X;
			result.Y = inverse * start.Y - amount * end.Y;
			result.Z = inverse * start.Z - amount * end.Z;
			result.W = inverse * start.W - amount * end.W;
			}

		result.Normalize();
		}

	/**
	 * 
	 * Performs a linear interpolation between two quaternions.
	 * 
	 * @param start The start quaternion.
	 * @param end The end quaternion.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @return Returns the interpolated quaternion.
	 */
	static FakeQuaternion Lerp(const FakeQuaternion &start, const FakeQuaternion &end, T amount)
		{
		FakeQuaternion result;
		Lerp(start, end, amount, result);
		return result;
		}

	/**
	 * 
	 * Creates a quaternion given a rotation and an axis.
	 * 
	 * @param axis The axis of rotation.
	 * @param angle The angle of rotation (in radians).
	 * @param result The result where the rotated quaternion is stored in.
	 */
	static void RotationAxis(const FakeVector3<T> &axis, T angle, FakeQuaternion &result)
		{
		FakeVector3<T> normalized;
		FakeVector3<T>::Normalize(axis, normalized);

		const T half = angle * static_cast<T>(0.5);
		const T sinHalf = fake_sin(half);
		const T cosHalf = fake_cos(half);

		result.X = normalized.X * sinHalf;
		result.Y = normalized.Y * sinHalf;
		result.Z = normalized.Z * sinHalf;
		result.W = cosHalf;
		}

	/**
	 * 
	 * Creates a quaternion given a angle cosine and an axis.
	 * 
	 * @param axis The axis of rotation.
	 * @param cos The angle cosine, it must be within [-1, 1] range (in radians).
	 * @param result The result where the rotated quaternion is stored in.
	 */
	static void RotationCosAxis(const FakeVector3<T> &axis, T cos, FakeQuaternion &result)
		{
		FakeVector3<T> normalized;
		FakeVector3<T>::Normalize(axis, normalized);

		const T cosHalf2 = (static_cast<T>(1.0) + cos) * static_cast<T>(0.5);
		const T sinHalf2 = static_cast<T>(1.0) - cosHalf2;
		const T cosHalf = fake_sqrt(cosHalf2);
		const T sinHalf = fake_sqrt(sinHalf2);

		result.X = normalized.X * sinHalf;
		result.Y = normalized.Y * sinHalf;
		result.Z = normalized.Z * sinHalf;
		result.W = cosHalf;
		}

	/**
	 * 
	 * Creates a quaternion given a rotation matrix.
	 * 
	 * @param matrix The rotation matrix.
	 * @param result The result where the rotated quaternion is stored in.
	 */
	static void RotationMatrix(const FakeMatrix4x4<T> &matrix, FakeQuaternion &result)
		{
		T sqrtV;
		T half;
		const T scale = matrix.M11 + matrix.M22 + matrix.M33;

		if (scale > static_cast<T>(0.0))
			{
			sqrtV = fake_sqrt(scale + static_cast<T>(1.0));
			result.W = sqrtV * static_cast<T>(0.5);
			sqrtV = static_cast<T>(0.5) / sqrtV;

			result.X = (matrix.M23 - matrix.M32) * sqrtV;
			result.Y = (matrix.M31 - matrix.M13) * sqrtV;
			result.Z = (matrix.M12 - matrix.M21) * sqrtV;
			}
		else if (matrix.M11 >= matrix.M22 && matrix.M11 >= matrix.M33)
			{
			sqrtV = fake_sqrt(static_cast<T>(1.0) + matrix.M11 - matrix.M22 - matrix.M33);
			half = static_cast<T>(0.5) / sqrtV;

			result = FakeQuaternion(
				static_cast<T>(0.5) * sqrtV,
				(matrix.M12 + matrix.M21) * half,
				(matrix.M13 + matrix.M31) * half,
				(matrix.M23 - matrix.M32) * half);
			}
		else if (matrix.M22 > matrix.M33)
			{
			sqrtV = fake_sqrt(static_cast<T>(1.0) + matrix.M22 - matrix.M11 - matrix.M33);
			half = static_cast<T>(0.5) / sqrtV;

			result = FakeQuaternion(
				(matrix.M21 + matrix.M12) * half,
				static_cast<T>(0.5) * sqrtV,
				(matrix.M32 + matrix.M23) * half,
				(matrix.M31 - matrix.M13) * half);
			}
		else
			{
			sqrtV = fake_sqrt(static_cast<T>(1.0) + matrix.M33 - matrix.M11 - matrix.M22);
			half = static_cast<T>(0.5) / sqrtV;

			result = FakeQuaternion(
				(matrix.M31 + matrix.M13) * half,
				(matrix.M32 + matrix.M23) * half,
				static_cast<T>(0.5) * sqrtV,
				(matrix.M12 - matrix.M21) * half);
			}

		result.Normalize();
		}

	/**
	 * 
	 * Creates a quaternion given a rotation matrix.
	 * 
	 * @param matrix The rotation matrix.
	 * @return Returns the rotated quaternion.
	 */
	static FakeQuaternion RotationMatrix(const FakeMatrix4x4<T> &matrix)
		{
		FakeQuaternion result;
		RotationMatrix(matrix, result);
		return result;
		}

	/**
	 * 
	 * Creates a left-handed, look-at quaternion.
	 * 
	 * @param eye The position of the viewer's eye (mostly camera position).
	 * @param target The camera look-at target (mostly object position).
	 * @param up The camera's up vector (mostly normal vector of the camera object).
	 * @param result The result where the lookAt projection is stored.
	 */
	static void LookAt(const FakeVector3<T> &eye, const FakeVector3<T> &target, const FakeVector3<T> &up, FakeQuaternion &result)
		{
		FakeMatrix4x4<T> matrix;
		FakeMatrix4x4<T>::LookAt(eye, target, up, matrix);
		RotationMatrix(matrix, result);
		}

	/**
	 * 
	 * Creates a left-handed, look-at quaternion.
	 * 
	 * @param forward The camera's forward direction.
	 * @param up The camera's up vector.
	 * @param result The result where the lookAt projection is stored.
	 */
	static void RotationLookAt(const FakeVector3<T> &forward, const FakeVector3<T> &up, FakeQuaternion &result)
		{
		LookAt(FakeVector3<T>::Zero, forward, up, result);
		}

	/**
	 * 
	 * Creates a left-handed spherical billboard that rotates around a specified object position.
	 * 
	 * @param objectPosition The position of the object around which the billboard will rotate.
	 * @param cameraPosition The position of the camera.
	 * @param cameraUpVector The up vector of the camera.
	 * @param cameraForwardVector The forward vector of the camera.
	 * @param result The result where the billboard projection is stored in.
	 */
	static void Billboard(const FakeVector3<T> &objectPosition, const FakeVector3<T> &cameraPosition, const FakeVector3<T> &cameraUpVector, const FakeVector3<T> &cameraForwardVector, FakeQuaternion &result)
		{
		FakeMatrix4x4<T> matrix;
		FakeMatrix4x4<T>::Billboard(objectPosition, cameraPosition, cameraUpVector, cameraForwardVector, matrix);
		RotationMatrix(matrix, result);
		}

	/**
	 * 
	 * Creates a rotation with the specified forward and upwards directions.
	 * 
	 * @param forward The forward direction. Direction to orient towards.
	 * @param up The up direction.
	 * @param result The result where the calculated quaternion will be stored in.
	 */
	static void LookRotation(const FakeVector3<T> &forward, const FakeVector3<T> &up, FakeQuaternion &result)
		{
		FakeVector3<T> forwardNorm = forward;
		forwardNorm.Normalize();
		FakeVector3<T> rightNorm;
		FakeVector3<T>::Cross(up, forwardNorm, rightNorm);
		rightNorm.Normalize();
		FakeVector3<T> upNorm;
		FakeVector3<T>::Cross(forwardNorm, rightNorm, upNorm);

		#define m00 rightNorm.X
		#define m01 rightNorm.Y
		#define m02 rightNorm.Z
		#define m10 upNorm.X
		#define m11 upNorm.Y
		#define m12 upNorm.Z
		#define m20 forwardNorm.X
		#define m21 forwardNorm.Y
		#define m22 forwardNorm.Z

		const T sum = m00 + m11 + m22;
		if (sum > 0)
			{
			const T num = fake_sqrt(sum + 1);
			const T invNumHalf = static_cast<T>(0.5) / num;
			result.X = (m12 - m21) * invNumHalf;
			result.Y = (m20 - m02) * invNumHalf;
			result.Z = (m01 - m10) * invNumHalf;
			result.W = num * static_cast<T>(0.5);
			}
		else if (m00 >= m11 && m00 >= m22)
			{
			const T num = fake_sqrt(static_cast<T>(1) + m00 - m11 - m22);
			const T invNumHalf = static_cast<T>(0.5) / num;
			result.X = static_cast<T>(0.5) * num;
			result.Y = (m01 + m10) * invNumHalf;
			result.Z = (m02 + m20) * invNumHalf;
			result.W = (m12 - m21) * invNumHalf;
			}
		else if (m11 > m22)
			{
			const T num = fake_sqrt(static_cast<T>(1) + m11 - m00 - m22);
			const T invNumHalf = static_cast<T>(0.5) / num;
			result.X = (m10 + m01) * invNumHalf;
			result.Y = static_cast<T>(0.5) * num;
			result.Z = (m21 + m12) * invNumHalf;
			result.W = (m20 - m02) * invNumHalf;
			}
		else
			{
			const T num = fake_sqrt(static_cast<T>(1) + m22 - m00 - m11);
			const T invNumHalf = static_cast<T>(0.5) / num;
			result.X = (m20 + m02) * invNumHalf;
			result.Y = (m21 + m12) * invNumHalf;
			result.Z = static_cast<T>(0.5) * num;
			result.W = (m01 - m10) * invNumHalf;
			}

		#undef m00
		#undef m01
		#undef m02
		#undef m10
		#undef m11
		#undef m12
		#undef m20
		#undef m21
		#undef m22
		}

	/**
	 * 
	 * Creates a rotation with the specified forward and upwards directions.
	 * 
	 * @param forward The forward direction. Direction to orient towards.
	 * @param up The up direction.
	 * @return Returns the calculated quaternion.
	 */
	static FakeQuaternion LookRotation(const FakeVector3<T> &forward, const FakeVector3<T> &up)
		{
		FakeQuaternion result;
		LookRotation(forward, up, result);
		return result;
		}

	/**
	 * 
	 * Gets the shortest arc quaternion to rotate this vector to the destination vector.
	 * 
	 * @param from The source vector.
	 * @param to The destination vector.
	 * @param fallbackAxis The fallback axis.
	 * @param result The result where the calculated quaternion will be stored in.
	 */
	static void GetRotation(const FakeVector3<T> &from, const FakeVector3<T> &to, const FakeVector3<T> &fallbackAxis, FakeQuaternion &result)
		{
		// Based on Stan Melax's article in Game Programming Gems

		FakeVector3<T> v0 = from;
		FakeVector3<T> v1 = to;
		v0.Normalize();
		v1.Normalize();

		const T d = FakeVector3<T>::Dot(v0, v1);

		// If dot == 1, vectors are the same
		if (d >= static_cast<T>(1.0))
			{
			result = Identity;
			return;
			}

		if (d < static_cast<T>(1e-6) - static_cast<T>(1.0))
			{
			if (fallbackAxis != FakeVector3<T>::Zero)
				{
				// Rotate 180 degrees about the fallback axis
				RotationAxis(fallbackAxis, FAKE_PI, result);
				}
			else
				{
				// Generate an axis
				FakeVector3<T> axis = FakeVector3<T>::Cross(FakeVector3<T>::UnitX, from);
				if (axis.LengthSquared() < ZeroTolerance) // Pick another if colinear
					axis = FakeVector3<T>::Cross(FakeVector3<T>::UnitY, from);
				axis.Normalize();
				RotationAxis(axis, FAKE_PI, result);
				}
			}
		else
			{
			const T s = fake_sqrt((static_cast<T>(1) + d) * static_cast<T>(2));
			const T invS = static_cast<T>(1) / s;

			FakeVector3<T> c;
			FakeVector3<T>::Cross(v0, v1, c);

			result.X = c.X * invS;
			result.Y = c.Y * invS;
			result.Z = c.Z * invS;
			result.W = s * static_cast<T>(0.5);
			result.Normalize();
			}
		}

	/**
	 * 
	 * Gets the shortest arc quaternion to rotate this vector to the destination vector.
	 * 
	 * @param from The source vector.
	 * @param to The destination vector.
	 * @param fallbackAxis The fallback axis.
	 * @return Returns the calculated quaternion.
	 */
	static FakeQuaternion GetRotation(const FakeVector3<T> &from, const FakeVector3<T> &to, const FakeVector3<T> &fallbackAxis)
		{
		FakeQuaternion result;
		GetRotation(from, to, fallbackAxis, result);
		return result;
		}

	/**
	 * 
	 * Gets the quaternion that will rotate vector from into vector to, around their plan perpendicular axis.The input vectors don't need to be normalized.
	 * 
	 * @param from The source vector.
	 * @param to The destination vector.
	 * @param result The result where the calculated quaternion will be stored in.
	 */
	static void FindBetween(const FakeVector3<T> &from, const FakeVector3<T> &to, FakeQuaternion &result)
		{
		// http://lolengine.net/blog/2014/02/24/quaternion-from-two-vectors-final
		const T normFromNormTo = fake_sqrt(from.LengthSquared() * to.LengthSquared());
		if (normFromNormTo < FAKE_ZERO_TOLERANCE)
			{
			result = Identity;
			return;
			}
		const float w = normFromNormTo + FakeVector3<T>::Dot(from, to);
		if (w < 1.e-6f * normFromNormTo)
			{
			result = FAKE_ABS(from.X) > FAKE_ABS(from.Z)
				? FakeQuaternion(-from.Y, from.X, 0.0f, 0.0f)
				: FakeQuaternion(0.0f, -from.Z, from.Y, 0.0f);
			}
		else
			{
			const FakeVector3<T> cross = FakeVector3<T>::Cross(from, to);
			result = FakeQuaternion(cross.X, cross.Y, cross.Z, w);
			}

		result.Normalize();
		}

	/**
	 * 
	 * Gets the quaternion that will rotate vector from into vector to, around their plan perpendicular axis.The input vectors don't need to be normalized.
	 * 
	 * @param from The source vector.
	 * @param to The destination vector.
	 * @return Returns the calculated quaternion.
	 */
	static FakeQuaternion FindBetween(const FakeVector3<T> &from, const FakeVector3<T> &to)
		{
		FakeQuaternion result;
		FindBetween(from, to, result);
		return result;
		}

	/**
	 * 
	 * Interpolates between two quaternions, using spherical linear interpolation.
	 * 
	 * @param start The start quaternion.
	 * @param end The end quaternion.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @param result The result where the interpolated quaternion is stored in.
	 */
	static void Slerp(const FakeQuaternion &start, const FakeQuaternion &end, T amount, FakeQuaternion &result)
		{
		T opposite;
		T inverse;
		const T dot = Dot(start, end);

		if (FAKE_ABS(dot) > static_cast<T>(1.0) - FAKE_ZERO_TOLERANCE)
			{
			inverse = static_cast<T>(1.0) - amount;
			opposite = amount * fake_sign(dot);
			}
		else
			{
			const T acos1 = fake_acos(FAKE_ABS(dot));
			const T invSin = static_cast<T>(1.0) / fake_sin(acos1);
			inverse = fake_sin((static_cast<T>(1.0) - amount) * acos1) * invSin;
			opposite = fake_sin(amount * acos1) * invSin * fake_sign(dot);
			}

		result.X = inverse * start.X + opposite * end.X;
		result.Y = inverse * start.Y + opposite * end.Y;
		result.Z = inverse * start.Z + opposite * end.Z;
		result.W = inverse * start.W + opposite * end.W;
		}

	/**
	 * 
	 * Interpolates between two quaternions, using spherical linear interpolation.
	 * 
	 * @param start The start quaternion.
	 * @param end The end quaternion.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @return Returns the interpolated quaternion.
	 */
	static FakeQuaternion Slerp(const FakeQuaternion &start, const FakeQuaternion &end, T amount)
		{
		FakeQuaternion result;
		Slerp(start, end, amount, result);
		return result;
		}

	/**
	 * 
	 * Creates a quaternion given a yaw, pitch, and roll value (in degrees).
	 * 
	 * @param x The roll value (in degrees).
	 * @param y The pitch value (in degrees).
	 * @param z The yaw value (in degrees).
	 * @return Returns a quaternion created with euler angles.
	 */
	static FakeQuaternion Euler(T x, T y, T z)
		{
		const T halfRoll = z * ((FAKE_PI / static_cast<T>(180.0)) * static_cast<T>(0.5));
		const T halfPitch = x * ((FAKE_PI / static_cast<T>(180.0)) * static_cast<T>(0.5));
		const T halfYaw = y * ((FAKE_PI / static_cast<T>(180.0)) * static_cast<T>(0.5));

		const T sinRollOver2 = fake_sin(halfRoll);
		const T cosRollOver2 = fake_cos(halfRoll);
		const T sinPitchOver2 = fake_sin(halfPitch);
		const T cosPitchOver2 = fake_cos(halfPitch);
		const T sinYawOver2 = fake_sin(halfYaw);
		const T cosYawOver2 = fake_cos(halfYaw);

		return FakeQuaternion(
			cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2,
			sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2,
			cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2,
			cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2);
		}

	/**
	 * 
	 * Creates a quaternion given a yaw, pitch, and roll value (in degrees).
	 * 
	 * @param euler The Euler angles in degrees (in raw, pitch, yaw order).
	 * @return Returns a quaternion created with euler angles.
	 */
	static FakeQuaternion Euler(const FakeVector3<T> &euler)
		{
		const T halfRoll = euler.Z * ((FAKE_PI / static_cast<T>(180.0)) * static_cast<T>(0.5));
		const T halfPitch = euler.X * ((FAKE_PI / static_cast<T>(180.0)) * static_cast<T>(0.5));
		const T halfYaw = euler.Y * ((FAKE_PI / static_cast<T>(180.0)) * static_cast<T>(0.5));

		const T sinRollOver2 = fake_sin(halfRoll);
		const T cosRollOver2 = fake_cos(halfRoll);
		const T sinPitchOver2 = fake_sin(halfPitch);
		const T cosPitchOver2 = fake_cos(halfPitch);
		const T sinYawOver2 = fake_sin(halfYaw);
		const T cosYawOver2 = fake_cos(halfYaw);

		return FakeQuaternion(
			cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2,
			sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2,
			cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2,
			cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2);
		}

	/**
	 * 
	 * Creates a quaternion given a yaw, pitch, and roll value (in radians).
	 * 
	 * @param yaw The yaw of the rotation (in radians).
	 * @param pitch The pitch of the rotation (in radians).
	 * @param roll The roll of the rotation (in radians).
	 * @param result The result where the euler rotation is stored in.
	 */
	static void RotationEuler(T yaw, T pitch, T roll, FakeQuaternion &result)
		{
		const T halfRoll = roll * static_cast<T>(0.5);
		const T halfPitch = pitch * static_cast<T>(0.5);
		const T halfYaw = yaw * static_cast<T>(0.5);

		const T sinRollOver2 = fake_sin(halfRoll);
		const T cosRollOver2 = fake_cos(halfRoll);
		const T sinPitchOver2 = fake_sin(halfPitch);
		const T cosPitchOver2 = fake_cos(halfPitch);
		const T sinYawOver2 = fake_sin(halfYaw);
		const T cosYawOver2 = fake_cos(halfYaw);

		result.W = cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2;
		result.X = cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2;
		result.Y = sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2;
		result.Z = cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2;
		}

	/**
	 * 
	 * Creates a quaternion given a yaw, pitch, and roll value (in radians).
	 * 
	 * @param yaw The yaw of the rotation (in radians).
	 * @param pitch The pitch of the rotation (in radians).
	 * @param roll The roll of the rotation (in radians).
	 * @return Returns the euler rotation as a quaternion.
	 */
	static FakeQuaternion RotationEuler(T yaw, T pitch, T roll)
		{
		FakeQuaternion result;
		RotationEuler(yaw, pitch, roll, result);
		return result;
		}

	/**
	 * 
	 * Adds two quaternions.
	 * 
	 * @param other The quaternion to add.
	 * @return Returns the sum of the two quaternions (other and current instance).
	 */
	FakeQuaternion operator+(const FakeQuaternion &other) const
		{
		FakeQuaternion result;
		Add(*this, other, result);
		return result;
		}

	/**
	 * 
	 * Subtracts two quaternions.
	 * 
	 * @param other The quaternion to subtract.
	 * @return Returns the difference of the two quaternions (other and current instance).
	 */
	FakeQuaternion operator-(const FakeQuaternion &other) const
		{
		FakeQuaternion result;
		Subtract(*this, other, result);
		return result;
		}

	/**
	 * 
	 * Multiplies two quaternions..
	 * 
	 * @param other The quaternion to multiply.
	 * @return Returns the multiplied quaternion.
	 */
	FakeQuaternion operator*(const FakeQuaternion &other) const
		{
		FakeQuaternion result;
		Multiply(*this, other, result);
		return result;
		}

	/**
	 * 
	 * Scales a quaternion by the given value.
	 * 
	 * @param scale The amount by which to scale the quaternion.
	 * @return Returns the scaled quaternion.
	 */
	FakeQuaternion operator*(T scale) const
		{
		FakeQuaternion q = this;
		q.Multiply(scale);
		return q;
		}

	/**
	 * 
	 * Adds two quaternions.
	 * 
	 * @param other The quaternion to add.
	 * @return Returns the sum of the two quaternions (other and the current instance).
	 */
	FakeQuaternion &operator+=(const FakeQuaternion &other)
		{
		X += other.X;
		Y += other.Y;
		Z += other.Z;
		W += other.W;
		return *this;
		}

	/**
	 * 
	 * Subtracts two quaternions.
	 * 
	 * @param other The quaternion to subtract.
	 * @return Returns the difference of the two quaternions (other and the current instance).
	 */
	FakeQuaternion &operator-=(const FakeQuaternion &other)
		{
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;
		W -= other.W;
		return *this;
		}

	/**
	 * 
	 * Multiplies two quaternions.
	 * 
	 * @param other The quaternion to multiply.
	 * @return Returns the multiplied quaternion.
	 */
	FakeQuaternion &operator*=(const FakeQuaternion &other)
		{
		Multiply(other);
		return *this;
		}

	/**
	 * 
	 * Scales a quaternion by the given value.
	 * 
	 * @param scale The amount by which to scale the quaternion.
	 * @return Returns the scaled quaternion.
	 */
	FakeQuaternion &operator*=(T scale)
		{
		Multiply(scale);
		return *this;
		}

	/**
	 * 
	 * Transforms a vector by the given rotation.
	 * 
	 * @param vector The vector to transform.
	 * @return Returns the scaled vector.
	 */
	FakeVector3<T> operator*(const FakeVector3<T> &vector) const
		{
		return FakeVector3<T>::Transform(vector, *this);
		}

	/**
	 * 
	 * Determines whether the specified quaternion is equal to this instance.
	 * 
	 * @param other The quaternion to compare with this instance.
	 * @return Returns true if the specified quaternion is equal to this instance - otherwise false.
	 */
	bool operator==(const FakeQuaternion &other) const
		{
		return Dot(*this, other) > static_cast<T>(0.99999999);
		}

	/**
	 *
	 * Determines whether the specified quaternion is not equal to this instance.
	 *
	 * @param other The quaternion to compare with this instance.
	 * @return Returns true if the specified quaternion is not equal to this instance - otherwise false.
	 */
	bool operator!=(const FakeQuaternion &other) const
		{
		return !(*this == other);
		}

	/**
	 * 
	 * Determines whether the specified quaternion is greater than this instance.
	 * 
	 * @param other The quaternion to compare with this instance.
	 * @return Returns true if the specified quaternion is greater than this instance - otherwise false.
	 */
	bool operator<(const FakeQuaternion &other) const
		{
		return X < other.X && Y < other.Y && Z < other.Z && W < other.W;
		}

	/**
	 * 
	 * Determines whether the specified quaternion is greater or equal to this instance.
	 * 
	 * @param other The quaternion to compare with this instance.
	 * @return Returns true if the specified quaternion is greater or equal to this instance - otherwise false.
	 */
	bool operator<=(const FakeQuaternion &other) const
		{
		return X <= other.X && Y <= other.Y && Z <= other.Z && W <= other.W;
		}

	/**
	 * 
	 * Determines whether the specified quaternion is less than this instance.
	 * 
	 * @param other The quaternion to compare with this instance.
	 * @return Returns true if the specified quaternion is less than this instance - otherwise false.
	 */
	bool operator>(const FakeQuaternion &other) const
		{
		return X > other.X && Y > other.Y && Z > other.Z && W > other.W;
		}

	/**
	 * 
	 * Determines whether the specified quaternion is less or equal to this instance.
	 * 
	 * @param other The quaternion to compare with this instance.
	 * @return Returns true if the specified quaternion is less or equal to this instance - otherwise false.
	 */
	bool operator>=(const FakeQuaternion &other) const
		{
		return X >= other.X && Y >= other.Y && Z >= other.Z && W >= other.W;
		}

	/**
	 * 
	 * Copy operator.
	 * 
	 * @param other The instance which should be copied.
	 * @return Returns the current instance.
	 */
	FakeQuaternion &operator=(const FakeQuaternion &other)
		{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		W = other.W;
		return *this;
		}

	/**
	 * 
	 * Overloaded dereferencing operator. Used to write the values of the quaternion into an array.
	 * 
	 * @return Returns the values of the quaternion in a stack based array.
	 */
	T *operator*()
		{
		static T arr[4];
		arr[0] = X;
		arr[1] = Y;
		arr[2] = Z;
		arr[3] = W;
		return arr;
		}

	/**
	 * 
	 * Overloaded dereferencing operator. Used to write the values of the quaternion into an array.
	 * 
	 * @return Returns the values of the quaternion in a stack based array.
	 */
	T *operator*() const
		{
		static T arr[4];
		arr[0] = X;
		arr[1] = Y;
		arr[2] = Z;
		arr[3] = W;
		return arr;
		}

	/**
	 * 
	 * Overloaded array indexing operators. Used to access the values of the quaternion in a array-style way.
	 * 
	 * @param index The index of the value to access. The index is always between 0 (including) and 4 (excluding).
	 * @return Returns the value of the quaternion at the specified index.
	 */
	T &operator[](size_t index)
		{
		FAKE_ASSERT(index < 4);
		return *((T*)this + index);
		}

	/**
	 * 
	 * Overloaded array indexing operators. Used to access the values of the quaternion in a array-style way.
	 * 
	 * @param index The index of the value to access. The index is always between 0 (including) and 4 (excluding).
	 * @return Returns the value of the quaternion at the specified index.
	 */
	const T &operator[](size_t index) const
		{
		FAKE_ASSERT(index < 4);
		return *((T*)this + index);
		}

	/**
	 * 
	 * Overloaded << operator, to print the quaternion into any stream.
	 * 
	 * @param stream The stream the quaternion should be written to.
	 * @param quaternion The quaternion which should be written.
	 * @return Returns the output stream containing the specified quaternion.
	 */
	friend std::ostream &operator<<(std::ostream &stream, const FakeQuaternion &quaternion)
		{
		stream << "Quaternion(" << quaternion.X << ", " << quaternion.Y << ", " << quaternion.Z << ", " << quaternion.W << ")";
		return stream;
		}
	};

template<typename T>
FakeQuaternion<T> FakeQuaternion<T>::Zero(static_cast<T>(0));

template<typename T>
FakeQuaternion<T> FakeQuaternion<T>::One(static_cast<T>(1));

template<typename T>
FakeQuaternion<T> FakeQuaternion<T>::Identity(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));

template<typename T>
inline FakeQuaternion<T> operator*(T scale, const FakeQuaternion<T> &other)
	{
	return other * scale;
	}

typedef FakeQuaternion<double> FakeQuatd;
typedef FakeQuaternion<float> FakeQuatf;
typedef FakeQuaternion<int32> FakeQuati;
typedef FakeQuaternion<long> FakeQuatl;
typedef FakeQuaternion<short> FakeQuats;
typedef FakeQuaternion<bool> FakeQuatb;

