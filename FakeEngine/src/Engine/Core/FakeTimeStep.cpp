#include "FakePch.h"
#include "FakeTimeStep.h"

FakeTimeStep::FakeTimeStep(double time)
    : Time(time)
    {
    }

FakeTimeStep::operator double() const
    {
    return Time;
    }

double FakeTimeStep::GetSeconds() const
    {
    return Time;
    }

double FakeTimeStep::GetMilliSeconds() const
    {
    return Time * 1000.0;
    }
