#include "Score.h"
#include <iostream>
Score::Score()
{
}

Score::~Score()
{
}

void Score::onNotify(int points, PointTypes event)
{
	switch (event)
	{
	case Additive:
		//adding points while the wave is running
		currentScore += points;
		break;
	case Multiplicative:
		multiplier += points;
		break;
	case Total:
		//this happens on the end of every wave
		totalScore += currentScore + static_cast<unsigned int>(currentScore * multiplier);
		//reset values
		currentScore = 0;
		multiplier = 1.0f;
	default:
		break;
	}
}

void Score::Init()
{
	totalScore = 0;
	currentScore = 0;
	multiplier = 1.0f;
}

 unsigned int Score::getTotal() 
{
	return totalScore + currentScore;

}

