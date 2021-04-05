#pragma once

#include "FakeProfiler.h"
#include "Engine/Core/DataTypes/FakeString.h"

namespace Utils
	{
	template <size_t N>
	struct ChangeResult
		{
		char Data[N];
		};

	template <size_t N, size_t K>
	constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
		ChangeResult<N> result = {};

		size_t srcIndex = 0;
		size_t dstIndex = 0;
		while (srcIndex < N)
			{
			size_t matchIndex = 0;
			
			while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
				{
				matchIndex++;
				}

			if (matchIndex == K - 1)
				{
				srcIndex += matchIndex;
				}

			result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
			srcIndex++;
			}

		return result;
		}
	}

class FakeProfilerTimer
	{
	private:
		FakeString Name;
		bool Stopped;
		std::chrono::time_point<std::chrono::steady_clock> StartPoint;

	public:

		FakeProfilerTimer(const FakeString &name)
			: Name(name), Stopped(false)
			{
			StartPoint = std::chrono::steady_clock::now();
			}

		~FakeProfilerTimer()
			{
			if (!Stopped)
				{
				Stop();
				}
			}

		void Stop()
			{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ StartPoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(StartPoint).time_since_epoch();

			FakeProfiler::Get().WriteProfile({ Name, highResStart, elapsedTime, std::this_thread::get_id() });
			Stopped = true;
			}
	};

#ifdef FAKE_ENABLE_PROFILER

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define FAKE_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define FAKE_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define FAKE_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define FAKE_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define FAKE_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define FAKE_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define FAKE_FUNC_SIG __func__
#else
#define HZ_FUNC_SIG "HZ_FUNC_SIG unknown!"
#endif

#define FAKE_PROFILE_BEGIN_SESSION(name, filepath) FakeProfiler::Get().BeginSession(name, filepath)
#define FAKE_PROFILE_END_SESSION() FakeProfiler::Get().EndSession()
#define FAKE_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = Utils::CleanupOutputString(name, "__cdecl "); FakeProfilerTimer timer##line(fixedName##line.Data);

#define FAKE_PROFILE_SCOPE_LINE(name, line) FAKE_PROFILE_SCOPE_LINE2(name, line)
#define FAKE_PROFILE_SCOPE(name) FAKE_PROFILE_SCOPE_LINE(name, __LINE__)
#define FAKE_PROFILE_FUNCTION() FAKE_PROFILE_SCOPE(FAKE_FUNC_SIG)

#else
#define FAKE_PROFILE_BEGIN_SESSION(name, filepath)
#define FAKE_PROFILE_END_SESSION()
#define FAKE_PROFILE_SCOPE(name)
#define FAKE_PROFILE_FUNCTION()
#endif