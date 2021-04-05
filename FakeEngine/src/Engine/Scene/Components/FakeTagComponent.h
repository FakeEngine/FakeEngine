#pragma once

struct FakeTagComponent
	{
	FakeString Tag;

	FakeTagComponent() = default;
	FakeTagComponent(const FakeTagComponent &) = default;
	FakeTagComponent(const FakeString &tag);

	};
