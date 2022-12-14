#pragma once
//random numbers
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


