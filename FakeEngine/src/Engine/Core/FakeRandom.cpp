#include "FakePch.h"
#include "FakeRandom.h"

void FakeRandom::Init()
	{
	RandomEngine.seed(std::random_device()());
	}

float FakeRandom::Float()
	{
	return (float)Distribution(RandomEngine) / (float)std::numeric_limits<uint32>::max();
	}

double FakeRandom::Double()
	{
	return (double)Distribution(RandomEngine) / (double)std::numeric_limits<uint32>::max();
	}

