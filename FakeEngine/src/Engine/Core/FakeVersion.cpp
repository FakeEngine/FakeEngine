#include "FakePch.h"
#include "FakeVersion.h"

FakeVersion::FakeVersion()
	: _Minor(0), _Major(0), _Build(0), _Revision(0)
	{
	}

FakeVersion::FakeVersion(int32 minor, int32 major, int32 build, int32 revision)
	{
	_Minor = FAKE_MAX(minor, 0);
	_Major = FAKE_MAX(major, 0);
	_Build = FAKE_MAX(build, 0);
	_Revision = FAKE_MAX(revision, 0);
	}

FakeVersion::FakeVersion(int32 minor, int32 major, int32 build)
	{
	_Minor = FAKE_MAX(minor, 0);
	_Major = FAKE_MAX(major, 0);
	_Build = FAKE_MAX(build, 0);
	_Revision = -1;
	}

FakeVersion::FakeVersion(int32 minor, int32 major)
	{
	_Minor = FAKE_MAX(minor, 0);
	_Major = FAKE_MAX(major, 0);
	_Build = -1;
	_Revision = -1;
	}

int32 FakeVersion::Build() const
	{
	return _Build;
	}

int32 FakeVersion::Minor() const
	{
	return _Minor;
	}

int16 FakeVersion::MinorRevision() const
	{
	return static_cast<int16>(_Revision >> 16);
	}

int32 FakeVersion::Major() const
	{
	return _Major;
	}

int16 FakeVersion::MajorRevision() const
	{
	return static_cast<int16>(_Revision & 65535);
	}

int32 FakeVersion::Revision() const
	{
	return _Revision;
	}

int32 FakeVersion::CompareTo(const FakeVersion &other) const
	{
	if (_Major != other._Major)
		{
		if (_Major > other._Major)
			return 1;
		return -1;
		}

	if (_Minor != other._Minor)
		{
		if (_Minor > other._Minor)
			return 1;
		return -1;
		}

	if (_Build != other._Build)
		{
		if (_Build > other._Build)
			return 1;
		return -1;
		}

	if (_Revision == other._Revision)
		return 0;

	if (_Revision > other._Revision)
		return 1;

	return -1;
	}

bool FakeVersion::Equals(const FakeVersion &other) const
	{
	return _Major == other._Major && _Minor == other._Minor && _Build == other._Build && _Revision == other._Revision;
	}

FakeString FakeVersion::ToString() const
	{
	if (_Build == -1)
		return ToString(2);

	if (_Revision == -1)
		return ToString(3);

	return ToString(4);
	}

FakeString FakeVersion::ToString(int32 fieldCount) const
	{
	FakeString result = "";

	switch (fieldCount)
		{
		case 0:
			break;

		case 1:
			result += FakeString::ToString(FAKE_MAX(_Major, 0));
			break;

		case 2:
			result += FakeString::ToString(FAKE_MAX(_Major, 0));
			result += ".";
			result += FakeString::ToString(FAKE_MAX(_Minor, 0));
			break;

		case 3:
			result += FakeString::ToString(FAKE_MAX(_Major, 0));
			result += ".";
			result += FakeString::ToString(FAKE_MAX(_Minor, 0));
			result += ".";
			result += FakeString::ToString(FAKE_MAX(_Build, 0));
			break;

		default:
			result += FakeString::ToString(FAKE_MAX(_Major, 0));
			result += ".";
			result += FakeString::ToString(FAKE_MAX(_Minor, 0));
			result += ".";
			result += FakeString::ToString(FAKE_MAX(_Build, 0));
			result += ".";
			result += FakeString::ToString(FAKE_MAX(_Revision, 0));
			break;
		}

	return result;
	}

bool FakeVersion::FromString(const FakeString &versionStr, FakeVersion *outValue)
	{
	//int32 major, minor, build, revision;

	/*
	!TODO!

	FakeArray<FakeString> parsedComponents(4);
	versionStr.Split('.', parsedComponents);

	int32 parsedComponentsLength = parsedComponents.GetCount();
	if (parsedComponentsLength < 2 || parsedComponentsLength > 4)
		return true;

	*/

	return false;
	}

bool FakeVersion::operator==(const FakeVersion &other) const
	{
	return Equals(other);
	}

bool FakeVersion::operator!=(const FakeVersion &other) const
	{
	return !(*this == other);
	}

bool FakeVersion::operator<(const FakeVersion &other) const
	{
	return CompareTo(other) < 0;
	}

bool FakeVersion::operator<=(const FakeVersion &other) const
	{
	return CompareTo(other) <= 0;
	}

bool FakeVersion::operator>(const FakeVersion &other) const
	{
	return CompareTo(other) > 0;
	}

bool FakeVersion::operator>=(const FakeVersion &other) const
	{
	return CompareTo(other) >= 0;
	}
