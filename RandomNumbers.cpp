#include "RandomNumbers.h"

void RandomNumbers::SetSeed()
{
	srand(static_cast<unsigned int>(time(0)));
}

void RandomNumbers::SetSeed(int seed)
{
	srand(seed);
}
//based on https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
float RandomNumbers::RandomBetweenFloats(float l, float h)
{
	return l + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (h - l)));
}
int RandomNumbers::RandomBetweenInts(int l, int h)
{
	return l + (rand()) / ((RAND_MAX / (h - l)));
}

RandomNumbers::RandomNumbers()
{
	SetSeed();
}

RandomNumbers::~RandomNumbers()
{
}
