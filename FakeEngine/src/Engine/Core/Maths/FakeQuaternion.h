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

#include "FakeMathFunctions.h"
#include "FakeVector2.h"
#include "FakeVector3.h"
#include "FakeVector4.h"
#include "FakeMatrix2x2.h"
#include "FakeMatrix3x3.h"
#include "FakeMatrix4x4.h"

template<typename T>
struct FakeQuaternion
	{
	union
		{
		struct
			{
			T X;
			T Y;
			T Z;
			T W;
			};

		T Raw[4];
		};

	static FakeQuaternion Zero;
	static FakeQuaternion One;
	static FakeQuaternion Identity;

	FakeQuaternion()
		{		}

	FakeQuaternion(T xyzw)
		: X(xyzw), Y(xyzw), Z(xyzw), W(xyzw)
		{		}

	FakeQuaternion(T x, T y, T z, T w)
		: X(x), Y(y), Z(z), W(w)
		{		}

	FakeQuaternion(const FakeVector3<T> &euler)
		{
		FakeVector3<T> c = { fake_cos(euler.X * static_cast<T>(0.5)), fake_cos(euler.Y * static_cast<T>(0.5)), fake_cos(euler.Z * static_cast<T>(0.5)) };
		FakeVector3<T> s = { fake_sin(euler.X * static_cast<T>(0.5)), fake_sin(euler.Y * static_cast<T>(0.5)), fake_sin(euler.Z * static_cast<T>(0.5)) };

		W = c.X * c.Y * c.Z + s.X * s.Y * s.Z;
		X = s.X * c.Y * c.Z - c.X * s.Y * s.Z;
		Y = c.X * s.Y * c.Z + s.X * c.Y * s.Z;
		Z = c.X * c.Y * s.Z - s.X * s.Y * c.Z;
		}

	FakeQuaternion(const FakeVector4<T> &v)
		: X(v.X), Y(v.Y), Z(v.Z), W(v.W)
		{		}

	FakeQuaternion(const FakeQuaternion &other)
		: X(other.X), Y(other.Y), Z(other.Z), W(other.W)
		{		}

	FakeString ToString() const
		{
		return FakeString::ToString(X) + ", " + FakeString::ToString(Y) + ", " + FakeString::ToString(Z) + ", " + FakeString::ToString(W);
		}

	static void ToMatrix3(const FakeQuaternion &other, FakeMatrix3x3<T> &result)
		{
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
		}

	static FakeMatrix3x3<T> ToMatrix3(const FakeQuaternion &other)
		{
		FakeMatrix3x3<T> result;
		ToMatrix3(other, result);
		return result;
		}

	static FakeMatrix4x4<T> ToMatrix4(const FakeQuaternion &other)
		{
		return FakeMatrix4x4<T>(ToMatrix3(other));
		}

	bool IsIdentity() const
		{
		return *this == Identity;
		}

	bool IsZero() const
		{
		return *this == Zero;
		}

	bool IsOne() const
		{
		return *this == One;
		}

	bool IsNormalized() const
		{
		return fake_is_one(X * X + Y * Y + Z * Z + W * W);
		}

	bool IsNaN() const
		{
		return isnan(X) || isnan(Y) || isnan(Z) || isnan(W);
		}

	bool IsInfinity() const
		{
		return isinf(X) || isinf(Y) || isinf(Z) || isinf(W);
		}

	bool IsNanOrInfinity() const
		{
		return IsNaN() || IsInfinity();
		}

	T Length() const
		{
		return fake_sqrt(X * X + Y * Y + Z * Z + W * W);
		}

	T LengthSquared() const
		{
		return X * X + Y * Y + Z * Z + W * W;
		}

	T GetAngle() const
		{
		const T length = X * X + Y * Y + Z * Z;
		if (fake_is_zero(length))
			return static_cast<T>(0);

		return static_cast<T>(2) * acosf(fake_clamp(W, static_cast<T>(-1), static_cast<T>(1)));
		}

	FakeVector3<T> GetAxis() const
		{
		const T length = X * X + Y * Y + Z * Z;
		if (fake_is_zero(length))
			return FakeVector3<T>::UnitX;

		const T inv = static_cast<T>(1) / fake_sqrt(length);
		return FakeVector3<T>(X * inv, Y * inv, Z * inv);
		}

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

		result *= static_cast<T>(180.0f / FAKE_PI);
		result.UnwindEuler();
		return result;
		}

	void Conjugate()
		{
		X = -X;
		Y = -Y;
		Z = -Z;
		}

	FakeQuaternion GetConjugate() const
		{
		return { -X, -Y, -Z, W };
		}

	void Inverse()
		{
		T lengthSq = LengthSquared();
		if (!fake_is_zero(lengthSq))
			{
			lengthSq = static_cast<T>(1) / lengthSq;
			X = -X * lengthSq;
			Y = -Y * lengthSq;
			Z = -Z * lengthSq;
			W = W * lengthSq;
			}
		}

	void Negate()
		{
		X = -X;
		Y = -Y;
		Z = -Z;
		W = -W;
		}

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

	static bool NearEqual(const FakeQuaternion &a, const FakeQuaternion &b)
		{
		return Dot(a, b) > static_cast<T>(0.99999999);
		}

	static bool NearEqual(const FakeQuaternion &a, const FakeQuaternion &b, T epsilon)
		{
		return Dot(a, b) > static_cast<T>(1) - epsilon;
		}

	static T Dot(const FakeQuaternion &a, const FakeQuaternion &b)
		{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;
		}

	static T AngleBetween(const FakeQuaternion &a, const FakeQuaternion &b)
		{
		const T dot = Dot(a, b);
		return dot > static_cast<T>(0.99999999) ? 0 : fake_acos(fake_min(FAKE_ABS(dot), static_cast<T>(1))) * static_cast<T>(2) * static_cast<T>(57.29578);
		}

	static void Inverse(const FakeQuaternion &value, FakeQuaternion &result)
		{
		result = value;
		result.Inverse();
		}

	static FakeQuaternion Inverse(const FakeQuaternion &value)
		{
		FakeQuaternion result;
		Inverse(value, result);
		return result;
		}

	static void Negate(const FakeQuaternion &value, FakeQuaternion &result)
		{
		result.X = -value.X;
		result.Y = -value.Y;
		result.Z = -value.Z;
		result.W = -value.W;
		}

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

	static FakeQuaternion Lerp(const FakeQuaternion &start, const FakeQuaternion &end, T amount)
		{
		FakeQuaternion result;
		Lerp(start, end, amount, result);
		return result;
		}

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

	static FakeQuaternion RotationAxis(const FakeVector3<T> &axis, T angle)
		{
		FakeQuaternion result;
		RotationAxis(axis, angle, result);
		return result;
		}

	static void RotationCosAxis(const FakeVector3<T> &axis, T cos, FakeQuaternion &result)
		{
		FakeVector3<T> normalized;
		FakeVector3<T>::Normalize(axis, normalized);

		const T cosHalf2 = (static_cast<T>(1) + cos) * static_cast<T>(0.5);
		const T sinHalf2 = static_cast<T>(1) - cosHalf2;
		const T cosHalf = fake_sqrt(cosHalf2);
		const T sinHalf = fake_sqrt(sinHalf2);

		result.X = normalized.X * sinHalf;
		result.Y = normalized.Y * sinHalf;
		result.Z = normalized.Z * sinHalf;
		result.W = cosHalf;
		}

	static void RotationMatrix(const FakeMatrix4x4<T> &matrix, FakeQuaternion &result)
		{
		T sqrtV;
		T half;
		const T scale = matrix.M11 + matrix.M22 + matrix.M33;

		if (scale > static_cast<T>(0))
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
			sqrtV = fake_sqrt(static_cast<T>(1) + matrix.M11 - matrix.M22 - matrix.M33);
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

	static FakeQuaternion RotationMatrix(const FakeMatrix4x4<T> &matrix)
		{
		FakeQuaternion result;
		RotationMatrix(matrix, result);
		return result;
		}

	static void LookAt(const FakeVector3<T> &eye, const FakeVector3<T> &target, const FakeVector3<T> &up, FakeQuaternion &result)
		{
		FakeMatrix4x4<T> matrix;
		FakeMatrix4x4<T>::LookAt(eye, target, up, matrix);
		RotationMatrix(matrix, result);
		}

	static void RotationLookAt(const FakeVector3<T> &forward, const FakeVector3<T> &up, FakeQuaternion &result)
		{
		LookAt(FakeVector3<T>::Zero, forward, up, result);
		}

	static void Billboard(const FakeVector3<T> &objectPosition, const FakeVector3<T> &cameraPosition, const FakeVector3<T> &cameraUpVector, const FakeVector3<T> &cameraForwardVector, FakeQuaternion &result)
		{
		FakeMatrix4x4<T> matrix;
		FakeMatrix4x4<T>::Billboard(objectPosition, cameraPosition, cameraUpVector, cameraForwardVector, matrix);
		RotationMatrix(matrix, result);
		}

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

	static FakeQuaternion LookRotation(const FakeVector3<T> &forward, const FakeVector3<T> &up)
		{
		FakeQuaternion result;
		LookRotation(forward, up, result);
		return result;
		}

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
				if (axis.LengthSquared() < FAKE_ZERO_TOLERANCE) // Pick another if colinear
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

	static FakeQuaternion GetRotation(const FakeVector3<T> &from, const FakeVector3<T> &to, const FakeVector3<T> &fallbackAxis)
		{
		FakeQuaternion result;
		GetRotation(from, to, fallbackAxis, result);
		return result;
		}

	static void FindBetween(const FakeVector3<T> &from, const FakeVector3<T> &to, FakeQuaternion &result)
		{
		// http://lolengine.net/blog/2014/02/24/quaternion-from-two-vectors-final
		const T normFromNormTo = fake_sqrt(from.LengthSquared() * to.LengthSquared());
		if (normFromNormTo < FAKE_ZERO_TOLERANCE)
			{
			result = Identity;
			return;
			}
		const T w = normFromNormTo + FakeVector3<T>::Dot(from, to);
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

	static FakeQuaternion FindBetween(const FakeVector3<T> &from, const FakeVector3<T> &to)
		{
		FakeQuaternion result;
		FindBetween(from, to, result);
		return result;
		}

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

	static FakeQuaternion Slerp(const FakeQuaternion &start, const FakeQuaternion &end, T amount)
		{
		FakeQuaternion result;
		Slerp(start, end, amount, result);
		return result;
		}

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

	static FakeQuaternion RotationEuler(T yaw, T pitch, T roll)
		{
		FakeQuaternion result;
		RotationEuler(yaw, pitch, roll, result);
		return result;
		}

	void Multiply(T scale)
		{
		X *= scale;
		Y *= scale;
		Z *= scale;
		W *= scale;
		}

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

	static void Add(const FakeQuaternion &a, const FakeQuaternion &b, FakeQuaternion &result)
		{
		result.X = a.X + b.X;
		result.Y = a.Y + b.Y;
		result.Z = a.Z + b.Z;
		result.W = a.W + b.W;
		}

	static void Subtract(const FakeQuaternion &a, const FakeQuaternion &b, FakeQuaternion &result)
		{
		result.X = a.X - b.X;
		result.Y = a.Y - b.Y;
		result.Z = a.Z - b.Z;
		result.W = a.W - b.W;
		}

	static void Multiply(const FakeQuaternion &a, const FakeQuaternion &b, FakeQuaternion &result)
		{
		const T aa = a.Y * b.Z - a.Z * b.Y;
		const T bb = a.Z * b.X - a.X * b.Z;
		const T cc = a.X * b.Y - a.Y * b.X;
		const T dd = a.X * b.X + a.Y * b.Y + a.Z * b.Z;

		result.X = a.X * b.W + b.X * a.W + aa;
		result.Y = a.Y * b.W + b.Y * a.W + bb;
		result.Z = a.Z * b.W + b.Z * a.W + cc;
		result.W = a.W * b.W - dd;
		}

	static void Multiply(const FakeQuaternion &a, T b, FakeQuaternion &result)
		{
		result.X = a.X * b;
		result.Y = a.Y * b;
		result.Z = a.Z * b;
		result.W = a.W * b;
		}

	static void Multiply(const FakeQuaternion &a, const FakeVector3<T> &b, FakeVector3<T> &result)
		{
		FakeVector3<T>::Transform(b, a, result);
		}

	static FakeQuaternion Add(const FakeQuaternion &a, const FakeQuaternion &b)
		{
		FakeQuaternion result;
		Add(a, b, result);
		return result;
		}

	static FakeQuaternion Subtract(const FakeQuaternion &a, const FakeQuaternion &b)
		{
		FakeQuaternion result;
		Subtract(a, b, result);
		return result;
		}

	static FakeQuaternion Multiply(const FakeQuaternion &a, const FakeQuaternion &b)
		{
		FakeQuaternion result;
		Multiply(a, b, result);
		return result;
		}

	static FakeQuaternion Multiply(const FakeQuaternion &a, T b)
		{
		FakeQuaternion result;
		Multiply(a, b, result);
		return result;
		}

	bool operator==(const FakeQuaternion &other) const
		{
		return X == other.X && Y == other.Y && Z == other.Z && W == other.W;
		}

	bool operator!=(const FakeQuaternion &other) const
		{
		return !(*this == other);
		}

	bool operator<(const FakeQuaternion &other) const
		{
		return X < other.X &&Y < other.Y &&Z < other.Z &&W < other.W;
		}

	bool operator<=(const FakeQuaternion &other) const
		{
		return X <= other.X && Y <= other.Y && Z <= other.Z && W <= other.W;
		}

	bool operator>(const FakeQuaternion &other) const
		{
		return X > other.X && Y > other.Y && Z > other.Z && W > other.W;
		}

	bool operator>=(const FakeQuaternion &other) const
		{
		return X >= other.X && Y >= other.Y && Z >= other.Z && W >= other.W;
		}

	FakeQuaternion operator-() const
		{
		return FakeQuaternion(-X, -Y, -Z, -W);
		}

	FakeQuaternion operator+(const FakeQuaternion &other) const
		{
		FakeQuaternion result;
		Add(*this, other, result);
		return result;
		}

	FakeQuaternion operator-(const FakeQuaternion &other) const
		{
		FakeQuaternion result;
		Subtract(*this, other, result);
		return result;
		}

	FakeQuaternion operator*(const FakeQuaternion &other) const
		{
		FakeQuaternion result;
		Multiply(*this, other, result);
		return result;
		}

	FakeQuaternion operator*(T scalar) const
		{
		FakeQuaternion result;
		Multiply(*this, scalar, result);
		return result;
		}

	FakeVector3<T> operator*(const FakeVector3<T> &vector) const
		{
		FakeVector3<T> result;
		Multiply(*this, vector, result);
		return result;
		}

	FakeQuaternion &operator+=(const FakeQuaternion &other)
		{
		Add(*this, other, *this);
		return *this;
		}

	FakeQuaternion &operator-=(const FakeQuaternion &other)
		{
		Subtract(*this, other, *this);
		return *this;
		}

	FakeQuaternion &operator*=(const FakeQuaternion &other)
		{
		Multiply(*this, other, *this);
		return *this;
		}

	FakeQuaternion &operator*=(T scalar)
		{
		Multiply(*this, scalar, *this);
		return *this;
		}

	FakeVector3<T> operator*=(const FakeVector3<T> &vector)
		{
		FakeVector3<T> result;
		Multiply(*this, vector, result);
		return result;
		}

	FakeQuaternion &operator++(int)
		{
		++X;
		++Y;
		++Z;
		++W;
		return *this;
		}

	FakeQuaternion &operator--(int)
		{
		--X;
		--Y;
		--Z;
		--W;
		return *this;
		}

	FakeQuaternion &operator=(const FakeQuaternion &other)
		{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		W = other.W;
		return *this;
		}

	T *operator*()
		{
		return Raw;
		}

	const T *operator*() const
		{
		return Raw;
		}

	T &operator[](uint32 index)
		{
		if (index > 0 && index < 4)
			{
			return Raw[index];
			}

		// Index out of bounds, return -1
		static T falseVal = static_cast<T>(-1);
		return falseVal;
		}

	const T &operator[](uint32 index) const
		{
		if (index > 0 && index < 4)
			{
			return Raw[index];
			}

		// Index out of bounds, return -1
		static T falseVal = static_cast<T>(-1);
		return falseVal;
		}

	friend std::ostream &operator<<(std::ostream &stream, const FakeQuaternion &quat)
		{
		stream << quat.X << ", " << quat.Y << ", " << quat.Z << ", " << quat.W;
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

