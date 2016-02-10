#include "RNG.h"

//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

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



