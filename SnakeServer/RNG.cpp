#include "RNG.h"

std::default_random_engine RNG::engine_{ std::random_device()() };

RNG::RNG()
{
}


RNG::~RNG()
{
}

int RNG::getInt(int lowerBound, int upperBound)
{
	std::uniform_int_distribution<int> dist(lowerBound, upperBound-1);
	return dist(engine_);
}



