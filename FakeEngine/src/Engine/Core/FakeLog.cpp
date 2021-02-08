#include "FakePch.h"
#include "FakeLog.h"

#include "Engine/Core/FakeTimer.h"
#include "Engine/Core/Maths/FakeMaths.h"

namespace Utils
	{
	template<typename T>
	static FakeString &Replace(FakeString &str, const FakeString &find, const T &replaceValue)
		{
		return str.Replace(find, FakeString::ToString(replaceValue), 1);
		}
	}

FakeLogLevel FakeLog::Severity = FakeLogLevel::None;
FakeRef<FakeConsole> FakeLog::Console = FakeConsole::Create();

void FakeLog::Print(const char *format, ...)
	{
	va_list args;
	FakeString out = format;
	va_start(args, format);

	int32 i = 0;
	while (out[i] != '\0')
		{
		if (out[i] == '%')
			{
			switch (out[i + 1])
				{
				case 'c':
					{
					char c = va_arg(args, char);
					out = Utils::Replace<char>(out, "%c", c);
					break;
					}

				case 's':
					{
					char *s = va_arg(args, char *);
					out = Utils::Replace<char *>(out, "%s", s);
					break;
					}

				case 'd':
					{
					int i = va_arg(args, int);
					out = Utils::Replace<int>(out, "%d", i);
					break;
					}

				case 'f':
					{
					double d = va_arg(args, double);
					out = Utils::Replace<double>(out, "%f", d);
					break;
					}

				case 'l':
					{
					if (out[i + 2] == 'l') // long long
						{
						long long l = va_arg(args, long long);
						out = Utils::Replace<long long>(out, "%ll", l);
						}
					else
						{
						long l = va_arg(args, long);
						out = Utils::Replace<long>(out, "%l", l);
						}
					break;
					}

				case 'm':
					{
					if (out[i + 2] == '2') // 2x2 Matrix
						{
						if (out[i + 3] == 'f') // float matrix
							{
							FakeMat2f mat = va_arg(args, FakeMat2f);
							out = Utils::Replace<FakeMat2f>(out, "%m2f", mat);
							}
						else if (out[i + 3] == 'i') // int matrix
							{
							FakeMat2i mat = va_arg(args, FakeMat2i);
							out = Utils::Replace<FakeMat2i>(out, "%m2i", mat);
							}
						else if (out[i + 3] == 'b') // bool matrix
							{
							FakeMat2b mat = va_arg(args, FakeMat2b);
							out = Utils::Replace<FakeMat2b>(out, "%m2b", mat);
							}
						}
					else if (out[i + 2] == '3') // 3x3 Matrix
						{
						if (out[i + 3] == 'f') // float matrix
							{
							FakeMat3f mat = va_arg(args, FakeMat3f);
							out = Utils::Replace<FakeMat3f>(out, "%m3f", mat);
							}
						else if (out[i + 3] == 'i') // int matrix
							{
							FakeMat3i mat = va_arg(args, FakeMat3i);
							out = Utils::Replace<FakeMat3i>(out, "%m3i", mat);
							}
						else if (out[i + 3] == 'b') // bool matrix
							{
							FakeMat3b mat = va_arg(args, FakeMat3b);
							out = Utils::Replace<FakeMat3b>(out, "%m3b", mat);
							}
						}
					else if (out[i + 2] == '4') // 4x4 Matrix
						{
						if (out[i + 3] == 'f') // float matrix
							{
							FakeMat4f mat = va_arg(args, FakeMat4f);
							out = Utils::Replace<FakeMat4f>(out, "%m4f", mat);
							}
						else if (out[i + 3] == 'i') // int matrix
							{
							FakeMat4i mat = va_arg(args, FakeMat4i);
							out = Utils::Replace<FakeMat4i>(out, "%m4i", mat);
							}
						else if (out[i + 3] == 'b') // bool matrix
							{
							FakeMat4b mat = va_arg(args, FakeMat4b);
							out = Utils::Replace<FakeMat4b>(out, "%m4b", mat);
							}
						}
					break;
					}

				case 'v':
					{
					if (out[i + 2] == '2') // Vector2
						{
						if (out[i + 3] == 'f') // float vector
							{
							FakeVec2f mat = va_arg(args, FakeVec2f);
							out = Utils::Replace<FakeVec2f>(out, "%v2f", mat);
							}
						else if (out[i + 3] == 'i') // int vector
							{
							FakeVec2i mat = va_arg(args, FakeVec2i);
							out = Utils::Replace<FakeVec2i>(out, "%v2i", mat);
							}
						else if (out[i + 3] == 'b') // bool vector
							{
							FakeVec2b mat = va_arg(args, FakeVec2b);
							out = Utils::Replace<FakeVec2b>(out, "%v2b", mat);
							}
						}
					else if (out[i + 2] == '3') // Vector3
						{
						if (out[i + 3] == 'f') // float vector
							{
							FakeVec3f vec = va_arg(args, FakeVec3f);
							out = Utils::Replace<FakeVec3f>(out, "%v3f", vec);
							}
						else if (out[i + 3] == 'i') // int vector
							{
							FakeVec3i vec = va_arg(args, FakeVec3i);
							out = Utils::Replace<FakeVec3i>(out, "%v3i", vec);
							}
						else if (out[i + 3] == 'b') // bool vector
							{
							FakeVec3b vec = va_arg(args, FakeVec3b);
							out = Utils::Replace<FakeVec3b>(out, "%v3b", vec);
							}
						}
					else if (out[i + 2] == '4') // Vector4
						{
						if (out[i + 3] == 'f') // float vector
							{
							FakeVec4f vec = va_arg(args, FakeVec4f);
							out = Utils::Replace<FakeVec4f>(out, "%v4f", vec);
							}
						else if (out[i + 3] == 'i') // int vector
							{
							FakeVec4i vec = va_arg(args, FakeVec4i);
							out = Utils::Replace<FakeVec4i>(out, "%v4i", vec);
							}
						else if (out[i + 3] == 'b') // bool vector
							{
							FakeVec4b vec = va_arg(args, FakeVec4b);
							out = Utils::Replace<FakeVec4b>(out, "%v4b", vec);
							}
						}
					break;
					}
				}
			}

		++i;
		}

	FakeConsoleForeground foreground;
	FakeConsoleBackground background = FakeConsoleBackground::BLACK;
	switch (Severity)
		{
		case FakeLogLevel::FatalLevel:
		case FakeLogLevel::ErrorLevel:
			foreground = FakeConsoleForeground::RED;
			break;

		case FakeLogLevel::InfoLevel:
			foreground = FakeConsoleForeground::BLUE;
			break;

		case FakeLogLevel::WarningLevel:
			foreground = FakeConsoleForeground::YELLOW;
			break;

		case FakeLogLevel::TraceLevel:
			foreground = FakeConsoleForeground::GREEN;
			break;

		case FakeLogLevel::None:
		default:
			foreground = FakeConsoleForeground::WHITE;
			break;
		}

	if (!Console)
		Console = FakeConsole::Create();

	va_end(args);
	Console->WriteLine("[" + FakeTimer::GetTimeStamp() + "] " + out, foreground, background);
	}

