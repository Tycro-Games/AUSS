#include "RandomNumbers.h"

void RandomNumbers::SetSeed()
{
	srand(time(0));
}

void RandomNumbers::SetSeed(int seed)
{
	srand(seed);
}

float RandomNumbers::RandomBetweenFloats(float l, float h)
{
	return l + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (h - l)));
}

RandomNumbers::RandomNumbers()
{
	SetSeed();
}

RandomNumbers::~RandomNumbers()
{
}
