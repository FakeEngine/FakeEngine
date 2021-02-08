#include "FakePch.h"
#include "FakeFileDialogueFilter.h"

void FakeFileDialogueFilter::AddFilter(const FakeString &name, const FakeString &format)
	{
	Filters.insert({ name, format });
	}

bool FakeFileDialogueFilter::HasFilters()
	{
	return Filters.size();
	}

std::map<FakeString, FakeString> &FakeFileDialogueFilter::GetFilters()
	{
	return Filters;
	}

