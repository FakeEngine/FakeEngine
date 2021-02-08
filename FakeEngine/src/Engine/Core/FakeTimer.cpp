#include "FakePch.h"
#include "FakeTimer.h"

FakeTimer::FakeTimer(const FakeString &name)
	: Name(name), Stopped(false)
	{
	StartPoint = std::chrono::high_resolution_clock::now();
	}

FakeTimer::~FakeTimer()
	{
	if (!Stopped)
		Stop();
	}

void FakeTimer::Stop()
	{
	auto endPoint = std::chrono::high_resolution_clock::now();

	long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(StartPoint).time_since_epoch().count();
	long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endPoint).time_since_epoch().count();

	FAKE_LOG_TRACE("%s Time: %llms", Name, (end - start));
	Stopped = true;
	}

double FakeTimer::GetTime()
	{
	auto now = std::chrono::system_clock::now().time_since_epoch();
	return (double)std::chrono::duration_cast<std::chrono::microseconds>(now).count();
	}

FakeString FakeTimer::GetTimeStamp(FakeDateFormat format, FakeTimePrecision precision)
	{
	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);
	FakeString result = "None";

	switch (format)
		{
		case FakeDateFormat::ENGLISH_US:
			{
			if (precision == FakeTimePrecision::MILLISECONDS || precision == FakeTimePrecision::NONE)
				{
				result = FakeString::ToString(std::put_time(&now, "%m/%d/%Y - %H:%M:%S"));
				}
			else if (precision == FakeTimePrecision::SECONDS)
				{
				result = FakeString::ToString(std::put_time(&now, "%m/%d/%Y - %H:%M"));
				}
			
			break;
			}

		case FakeDateFormat::ENGLISH_GB:
			{
			if (precision == FakeTimePrecision::MILLISECONDS || precision == FakeTimePrecision::NONE)
				{
				result = FakeString::ToString(std::put_time(&now, "%d/%m/%Y - %H:%M:%S"));
				}
			else if (precision == FakeTimePrecision::SECONDS)
				{
				result = FakeString::ToString(std::put_time(&now, "%d/%m/%Y - %H:%M"));
				}

			break;
			}

		default:
		case FakeDateFormat::GERMAN:
			{
			if (precision == FakeTimePrecision::MILLISECONDS || precision == FakeTimePrecision::NONE)
				{
				result = FakeString::ToString(std::put_time(&now, "%d.%m.%Y - %H:%M:%S"));
				}
			else if (precision == FakeTimePrecision::SECONDS)
				{
				result = FakeString::ToString(std::put_time(&now, "%d.%m.%Y - %H:%M"));
				}

			break;
			}
		}

	return result;
	}

FakeString FakeTimer::GetCurrentSecond()
	{
	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);
	return FakeString::ToString(now.tm_sec);
	}

FakeString FakeTimer::GetCurrentMinute()
	{
	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);
	return FakeString::ToString(now.tm_min);
	}

FakeString FakeTimer::GetCurrentHour()
	{
	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);
	return FakeString::ToString(now.tm_hour);
	}

FakeString FakeTimer::GetCurrentDay()
	{
	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);
	return FakeString::ToString(now.tm_mday);
	}

FakeString FakeTimer::GetCurrentMonth()
	{
	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);
	return FakeString::ToString(now.tm_mon + 1);
	}

FakeString FakeTimer::GetCurrentYear()
	{
	std::time_t t = std::time(0);
	std::tm now;
	localtime_s(&now, &t);
	return FakeString::ToString(now.tm_year + 1900);
	}
