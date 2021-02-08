#include "FakePch.h"
#include "FakeEventsBase.h"

FakeString FakeEvent::ToString() const
	{
	return GetName();
	}

bool FakeEvent::IsInCategory(FakeEventCategory c)
	{
	return GetCategoryFlags() & c;
	}

inline std::ostream &operator<<(std::ostream &stream, const FakeEvent &e)
	{
	return stream << e.ToString();
	}

