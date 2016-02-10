#ifndef RNG_H
#define RNG_H

#include <random>

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

