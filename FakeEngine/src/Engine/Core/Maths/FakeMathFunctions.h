/*****************************************************************
 * \file   FakeMathFunctions.h
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

#include <math.h>
#include "Engine/Core/FakeCore.h"

#define FAKE_PI 3.1415926535897932f
#define FAKE_TWO_PI 6.28318530718f
#define FAKE_PI_INV 0.31830988618f
#define FAKE_PI_OVER_2 1.57079632679f
#define FAKE_PI_OVER_4 0.78539816339f
#define FAKE_PI_HALF FAKE_PI_OVER_2

// The value for which all absolute numbers smaller than are considered equal to zero.
#define FAKE_ZERO_TOLERANCE 1e-6f

static double fake_mod(const double x, const double y)
	{
	return fmod(x, y);
	}

static float fake_mod(const float x, const float y)
	{
	return fmodf(x, y);
	}

static float fake_modf(const float x, float *y)
	{
	return modff(x, y);
	}

static float fake_exp(const float x)
	{
	return expf(x);
	}

static float fake_exp2(const float x)
	{
	return exp2f(x);
	}

static float fake_trunk(float x)
	{
	return truncf(x);
	}

static float fake_fractional(float x)
	{
	return x - fake_trunk(x);
	}

static int32 fake_trunk_to_int(float x)
	{
	return (int32) x;
	}

static int32 fake_floor_to_int(float x)
	{
	return fake_trunk_to_int(floorf(x));
	}

static int32 fake_round_to_int(float x)
	{
	return fake_floor_to_int(x + 0.5f);
	}

static int32 fake_ceil_to_int(float x)
	{
	return fake_trunk_to_int(ceilf(x));
	}

static int32 fake_round_up_to_power_of_2(int32 x)
	{
	// @see: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

	if (x < 0)
		return 0;

	x++;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
	}

static uint32 fake_round_up_to_power_of_2(uint32 x)
	{
	// @see: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

	x++;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
	}

static int64 fake_round_up_to_power_of_2(int64 x)
	{
	// @see: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

	if (x < 0)
		return 0;

	x++;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	return x + 1;
	}

static uint64 fake_round_up_to_power_of_2(uint64 x)
	{
	// @see: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

	x++;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	return x + 1;
	}

static double fake_round(double x)
	{
	return round(x);
	}

static float fake_round(float x)
	{
	return roundf(x);
	}

static double fake_floor(double x)
	{
	return floor(x);
	}

static float fake_floor(float x)
	{
	return floorf(x);
	}

static double fake_ceil(double x)
	{
	return ceil(x);
	}

static float fake_ceil(float x)
	{
	return ceilf(x);
	}

static double fake_sin(double x)
	{
	// TEMP
	return sin(x);
	}

static float fake_sin(float x)
	{
	// TEMP
	return sinf(x);
	}

static double fake_asin(double x)
	{
	// TEMP
	return asin(x);
	}

static float fake_asin(float x)
	{
	// TEMP
	return asinf(x);
	}

static double fake_sinh(double x)
	{
	// TEMP
	return sinh(x);
	}

static float fake_sinh(float x)
	{
	// TEMP
	return sinhf(x);
	}

static double fake_cos(double x)
	{
	// TEMP
	return cos(x);
	}

static float fake_cos(float x)
	{
	// TEMP
	return cosf(x);
	}

static double fake_acos(double x)
	{
	// TEMP
	return acos(x < -1.f ? -1.f : x < 1.f ? x : 1.f);
	}

static float fake_acos(float x)
	{
	// TEMP
	return acosf(x < -1.f ? -1.f : x < 1.f ? x : 1.f);
	}

static double fake_tan(double x)
	{
	// TEMP
	return tan(x);
	}

static float fake_tan(float x)
	{
	// TEMP
	return tanf(x);
	}

static double fake_atan(double x)
	{
	// TEMP
	return atan(x);
	}

static float fake_atan(float x)
	{
	// TEMP
	return atanf(x);
	}

static double fake_atan2(double x, double y)
	{
	// TEMP
	return atan2(x, y);
	}

static float fake_atan2(float x, float y)
	{
	// TEMP
	return atan2f(x, y);
	}

static void fake_sin_cos(float radians, float &sine, float &cosine)
	{
	sine = fake_sin(radians);
	cosine = fake_cos(radians);
	}

static uint32 fake_floor_log2(uint32 x)
	{
	// References:
	// http://codinggorilla.domemtech.com/?p=81
	// http://en.wikipedia.org/wiki/Binary_logarithm

	uint32 pos = 0;

	if (x >= 1 << 16)
		{
		x >>= 16;
		pos += 16;
		}

	if (x >= 1 << 8)
		{
		x >>= 8;
		pos += 8;
		}

	if (x >= 1 << 4)
		{
		x >>= 4;
		pos += 4;
		}

	if (x >= 1 << 2)
		{
		x >>= 2;
		pos += 2;
		}

	if (x >= 1 << 1)
		{
		pos += 1;
		}

	return x == 0 ? 0 : pos;
	}

static bool fake_is_power_of_two(uint32 x)
	{
	return (x & x - 1) == 0;
	}

static float fake_smooth_step(float x)
	{
	return x <= 0 ? 0 : x >= 1 ? 1 : x * x * (3 - 2 * x);
	}

static float fake_smooth_step(float x, float y, float a)
	{
	if (a < x)
		return 0.0f;

	if (a >= y)
		return 1.0f;

	const float fraction = (a - x) / (y - x);
	return fraction * fraction * (3.0f - 2.0f * fraction);
	}

static float fake_smoother_step(float x)
	{
	return x <= 0.0f ? 0.0f : x >= 1 ? 1 : x * x * x * (x * (x * 6.0f - 15.0f) + 10.0f);
	}

inline bool fake_is_zero(double x)
	{
	return FAKE_ABS(x) < 1e-7;
	}

inline bool fake_is_zero(float x)
	{
	return FAKE_ABS(x) < FAKE_ZERO_TOLERANCE;
	}

inline bool fake_is_one(float x)
	{
	return fake_is_zero(x - 1.0f);
	}

inline float fake_sign(float x)
	{
	return x > 0.0f ? 1.0f : x < 0.0f ? -1.0f : 0.0f;
	}

inline bool fake_same_sign(const float x, const float y)
	{
	return x * y >= 0.0f;
	}

inline bool fake_not_same_sign(const float x, const float y)
	{
	return x * y < 0.0f;
	}

static bool fake_near_equal(float x, float y)
	{
	// Check if the numbers are really close - needed when comparing numbers near zero
	if (fake_is_zero(x - y))
		return true;

	// Original from Bruce Dawson: http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
	const int32 xInt = *(int32 *) &x;
	const int32 yInt = *(int32 *) &y;

	// Different signs means they do not match
	if (xInt < 0 != yInt < 0)
		return false;

	// Find the difference in ULPs
	const int ulp = FAKE_ABS(xInt - yInt);

	// Choose of maxUlp = 4
	// according to http://code.google.com/p/googletest/source/browse/trunk/include/gtest/internal/gtest-internal.h
	const int maxUlp = 4;
	return ulp <= maxUlp;
	}

static bool fake_not_near_equal(float x, float y)
	{
	// Check if the numbers are really close - needed when comparing numbers near zero
	if (fake_is_zero(x - y))
		return false;

	// Original from Bruce Dawson: http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
	const int32 xInt = *(int32 *) &x;
	const int32 yInt = *(int32 *) &y;

	// Different signs means they do not match
	if (xInt < 0 != yInt < 0)
		return true;

	// Find the difference in ULPs
	const int ulp = FAKE_ABS(xInt - yInt);

	// Choose of maxUlp = 4
	// according to http://code.google.com/p/googletest/source/browse/trunk/include/gtest/internal/gtest-internal.h
	const int maxUlp = 4;
	return ulp > maxUlp;
	}

static bool fake_near_equal(float x, float y, float eps)
	{
	return FAKE_ABS(x - y) < eps;
	}

static float fake_remap(float x, float fromMin, float fromMax, float toMin, float toMax)
	{
	return (x - fromMin) / (fromMax - fromMin) * (toMax - toMin) + toMin;
	}

static float fake_clamp_axis(float angle)
	{
	angle = fake_mod(angle, 360.0f);

	if (angle < 0.0f)
		angle += 360.0f;

	return angle;
	}

static float fake_normalize_axis(float angle)
	{
	angle = fake_clamp_axis(angle);

	if (angle > 180.0f)
		angle -= 360.0f;

	return angle;
	}

static float fake_find_delta_angle(float a1, float a2)
	{
	float delta = a2 - a1;
	if (delta > FAKE_PI)
		delta = delta - FAKE_PI * 2.0f;
	else if (delta < -FAKE_PI)
		delta = delta + FAKE_PI * 2.0f;
	return delta;
	}

static float fake_unwind_radians(float x)
	{
	while (x > FAKE_PI)
		x -= (float) FAKE_PI * 2.0f;

	while (x < -FAKE_PI)
		x += (float) FAKE_PI * 2.0f;

	return x;
	}

static float fake_unwind_degrees(float x)
	{
	while (x > 180.0f)
		x -= 360.0f;

	while (x < -180.0f)
		x += 360.0f;

	return x;
	}

static float fake_floor_select(float comparand, float valueGEZero, float valueLTZero)
	{
	return comparand >= 0.0f ? valueGEZero : valueLTZero;
	}

template<typename T>
static T fake_radians(T degrees)
	{
	return degrees * static_cast<T>(FAKE_PI * 180.0f);
	}

template<typename T>
static T fake_degrees(T radians)
	{
	return radians * static_cast<T>(180.0f / FAKE_PI);
	}

template<typename T>
static T fake_min()
	{
	return std::numeric_limits<T>::min();
	}

template<typename T>
static T fake_max()
	{
	return std::numeric_limits<T>::max();
	}

template<typename T>
static T fake_faculty(T num)
	{
	T ret = static_cast<T>(1);
	T i;

	for (i = ret; i <= num; ++i)
		ret *= i;

	return ret;
	}

template<typename T>
static T fake_pow(T basis, uint32 potenz)
	{
	if (static_cast<T>(0) == potenz)
		return static_cast<T>(1);

	T ret = basis;
	uint32 i;

	for (i = 0; i < potenz; ++i)
		ret *= basis;

	return ret;
	}

template<typename T>
static T fake_sqrt(T x)
	{
	// HINT: fake_sqrt returns wrong values if ints are provided as argument
	T ret = static_cast<T>(1);
	uint32 i;

	for (i = 0; i <= 10; ++i)
		ret -= (ret * ret - x) / (static_cast<T>(2) * ret);

	return ret;
	}

template<typename T>
static T fake_divide_by_multiple(T value, T alignment)
	{
	T mask = alignment - 1;
	return (T) ((value + mask) / alignment);
	}

template<typename T>
static T fake_divide_and_round_up(T dividend, T divisor)
	{
	return (dividend + divisor - 1) / divisor;
	}

template<typename T>
static T fake_divide_and_round_down(T dividend, T divisor)
	{
	return dividend / divisor;
	}

template<typename T>
static bool fake_is_in_range(const T value, const T min, const T max)
	{
	return value >= min && value <= max;
	}

template<typename T>
static bool fake_is_not_in_range(const T value, const T min, const T max)
	{
	return value < min || value > max;
	}

template<typename T>
static T fake_clamp(const T value, const T min, const T max)
	{
	return value < min ? min : value < max ? value : max;
	}

template<typename T>
static T fake_saturate(const T x)
	{
	return x < 0 ? 0 : x < 1 ? x : 1;
	}

template<typename T>
static T fake_average_arithmetic(const T x, const T y)
	{
	return (x + y) * static_cast<T>(0.5);
	}

template<typename T>
static T fake_min(const T x, const T y)
	{
	return x < y ? x : y;
	}

template<typename T>
static T fake_min(const T x, const T y, const T z)
	{
	return fake_min(fake_min(x, y), z);
	}

template<typename T>
static T fake_min(const T x, const T y, const T z, const T w)
	{
	return fake_min(fake_min(fake_min(x, y), z), w);
	}

template<typename T>
static T fake_max(const T x, const T y)
	{
	return x > y ? x : y;
	}

template<typename T>
static T fake_max(const T x, const T y, const T z)
	{
	return fake_max(fake_max(x, y), z);
	}

template<typename T>
static T fake_max(const T x, const T y, const T z, const T w)
	{
	return fake_max(fake_max(fake_max(x, y), z), w);
	}

template<typename T, typename U>
static T fake_lerp(const T &x, const T &y, const U &alpha)
	{
	return (T) (x + alpha * (y - x));
	}

template<typename T>
static T fake_lerp_stable(const T &x, const T &y, double alpha)
	{
	return (T) (x * (1.0 - alpha) + y * alpha);
	}

template<typename T>
static T fake_lerp_stable(const T &x, const T &y, float alpha)
	{
	return (T) (x * (1.0f - alpha) + y * alpha);
	}

template<typename T>
static T fake_align_up_with_mask(T value, T mask)
	{
	return (T) (value + mask & ~mask);
	}

template<typename T>
static T align_down_with_mask(T value, T mask)
	{
	return (T) (value & ~mask);
	}

template<typename T>
static T fake_align_up(T value, T alignment)
	{
	T mask = alignment - 1;
	return (T) (value + mask & ~mask);
	}

template<typename T>
static T fake_align_down(T value, T alignment)
	{
	T mask = alignment - 1;
	return (T) (value & ~mask);
	}

template<typename T>
static bool fake_is_aligned(T value, T alignment)
	{
	T mask = alignment - 1;
	return 0 == (value & mask);
	}

template<typename T, typename U>
static T fake_cubic_interp(const T &p0, const T &p1, const T &t0, const T &t1, const U &alpha)
	{
	const float alpha2 = alpha * alpha;
	const float alpha3 = alpha2 * alpha;

	return (T) ((2 * alpha3 - 3 * alpha2 + 1) * p0)
		+ (alpha3 - 2 * alpha2 + alpha) * t0
		+ (alpha3 - alpha2) * t1
		+ (-2 * alpha3 + 3 * alpha2) * p1;
	}

template<typename T>
static T fake_interp_ease_in(const T &x, const T &y, float alpha, float exponent)
	{
	const float blend = fake_pow(alpha, exponent);
	return fake_lerp<T>(x, y, blend);
	}

template<typename T>
static T fake_interp_ease_out(const T &x, const T &y, float alpha, float exponent)
	{
	const float blend = 1.0f - fake_pow(1.0f - alpha, exponent);
	return fake_lerp<T>(x, y, blend);
	}

template<typename T>
static T fake_interp_ease_in_out(const T &x, const T &y, float alpha, float exponent)
	{
	const float blend = alpha < 0.5f ? fake_interp_ease_in(0.0f, 1.0f, alpha * 2.0f, exponent) * 0.5f : fake_interp_ease_out(0.0f, 1.0f, alpha * 2.0f - 1.0f, exponent) * 0.5f + 0.5f;
	return fake_lerp<T>(x, y, blend);
	}

template<typename T>
static T fake_interp_sin_in(const T &x, const T &y, float alpha)
	{
	const float blend = -1.0f * fake_cos(alpha * FAKE_PI_HALF) + 1.0f;
	return fake_lerp<T>(x, y, blend);
	}

template<typename T>
static T fake_interp_sin_out(const T &x, const T &y, float alpha)
	{
	const float blend = fake_sin(alpha * FAKE_PI_HALF);
	return fake_lerp<T>(x, y, blend);
	}

template<typename T>
static T fake_interp_sin_in_out(const T &x, const T &y, float alpha)
	{
	const float blend = alpha < 0.5f ? fake_interp_sin_in(0.0f, 1.0f, alpha * 2.0f) * 0.5f : fake_interp_sin_out(0.0f, 1.0f, alpha * 2.0f - 1.0f) * 0.5f + 0.5f;
	return fake_lerp<T>(x, y, blend);
	}

template<typename T>
static T fake_interp_expo_in(const T &x, const T &y, float alpha)
	{
	const float blend = alpha == 0.0f ? 0.0f : fake_pow(2.0f, 10.0f * (alpha - 1.0f));
	return fake_lerp<T>(x, y, blend);
	}

template<typename T>
static T fake_interp_expo_out(const T &x, const T &y, float alpha)
	{
	const float blend = alpha == 1.0f ? 1.0f : -fake_pow(2.0f, -10.0f * alpha) + 1.0f;
	return fake_lerp<T>(x, y, blend);
	}

template<typename T>
static T fake_interp_expo_in_out(const T &x, const T &y, float alpha)
	{
	const float blend = alpha < 0.5f ? fake_interp_expo_in(0.0f, 1.0f, alpha * 2.0f) * 0.5f : fake_interp_expo_out(0.0f, 1.0f, alpha * 2.0f - 1.0f) * 0.5f + 0.5f;
	return fake_lerp<T>(x, y, blend);
	}

template<typename T>
static T fake_interp_circular_in(const T &x, const T &y, float alpha)
	{
	const float blend = -1.0f * (fake_sqrt(1.0f - alpha * alpha) - 1.0f);
	return fake_lerp<T>(x, y, blend);
	}

template<typename T>
static T fake_interp_circular_out(const T &x, const T &y, float alpha)
	{
	alpha -= 1.0f;
	const float blend = fake_sqrt(1.0f - alpha * alpha);
	return fake_lerp<T>(x, y, blend);
	}

template<typename T>
static T fake_interp_circular_in_out(const T &x, const T &y, float alpha)
	{
	const float blend = alpha < 0.5f ? fake_interp_circular_in(0.0f, 1.0f, alpha * 2.0f) * 0.5f : fake_interp_circular_out(0.0f, 1.0f, alpha * 2.0f - 1.0f) * 0.5f + 0.5f;
	return fake_lerp<T>(x, y, blend);
	}

