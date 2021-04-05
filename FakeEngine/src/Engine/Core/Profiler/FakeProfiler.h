#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

#include "FakeProfilerSession.h"

using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

struct FakeProfileResult
	{
	FakeString Name;

	FloatingPointMicroseconds Start;
	std::chrono::microseconds ElapsedTime;
	std::thread::id ThreadID;
	};

class FakeProfiler
	{
	private:
		std::mutex Mutex;
		std::ofstream OutputStream;
		FakeProfilerSession *CurrentSession;

		FakeProfiler()
			: CurrentSession(nullptr)
			{
			}

		~FakeProfiler()
			{
			EndSession();
			}

		void WriteHeader()
			{
			OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			OutputStream.flush();
			}

		void WriteFooter()
			{
			OutputStream << "]}";
			OutputStream.flush();
			}

		void InternalEndSession()
			{
			if (CurrentSession)
				{
				WriteFooter();
				OutputStream.close();
				delete CurrentSession;
				CurrentSession = nullptr;
				}
			}

	public:

		// Delete move and copy constructor
		FakeProfiler(const FakeProfiler&) = delete;
		FakeProfiler(FakeProfiler&&) = delete;

		void BeginSession(const std::string &name, const std::string &filepath = "results.json")
			{
			std::lock_guard lock(Mutex);
			if (CurrentSession)
				{
				// If there is already a current session, then close it before beginning new one.
				// Subsequent profiling output meant for the original session will end up in the
				// newly opened session instead.  That's better than having badly formatted
				// profiling output.
				InternalEndSession();
				}
			OutputStream.open(filepath);

			if (OutputStream.is_open())
				{
				CurrentSession = new FakeProfilerSession({ name });
				WriteHeader();
				}
			}

		void EndSession()
			{
			std::lock_guard lock(Mutex);
			InternalEndSession();
			}

		void WriteProfile(const FakeProfileResult &result)
			{
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(Mutex);
			if (CurrentSession)
				{
				OutputStream << json.str();
				OutputStream.flush();
				}
			}

		static FakeProfiler &Get()
			{
			static FakeProfiler instance;
			return instance;
			}
	};

