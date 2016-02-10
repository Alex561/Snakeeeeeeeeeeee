#ifndef RNG_H
#define RNG_H

#include <random>

//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

class RNG
{
public:
	RNG();
	~RNG();

	//returns a random number between lower (inclusive) and upper (exclusive)
	static int getInt(int lowerBound, int upperBound);

private:
	static std::default_random_engine engine_;
};

#endif //RNG_H

