#pragma once
//random numbers
#include <cstdlib>
#include <ctime>
#include "template.h"
class RandomNumbers
{
public:
	void SetSeed();
	void SetSeed(int);
	float RandomBetweenFloats(float, float);
	int RandomBetweenInts(int, int);
	float RandomMinusPlusSign();
	RandomNumbers();
	~RandomNumbers() = default;

private:

};


