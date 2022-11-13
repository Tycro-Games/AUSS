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
/// <summary>
/// returns a random int
/// </summary>
/// <param name="l">inclusive</param>
/// <param name="h">exclusive</param>
/// <returns> </returns>
int RandomNumbers::RandomBetweenInts(int l, int h)
{
	return l + (rand()) % (h - l);
}

RandomNumbers::RandomNumbers()
{
	SetSeed();
}

RandomNumbers::~RandomNumbers()
{
}
