#include "Score.h"
#include <iostream>




void Score::onNotify(int points, EventType eventt)
{
	switch (eventt)
	{
	case EventType::EnemyDeath:
		//adding points while the wave is running
		currentScore += points;
		break;
	case EventType::BonusConditions: //like having a high accuracy or not being hit by enemies for an entire wave
		//add to the multiplier
		multiplier += points;
		break;
	case EventType::EndOfAWave:
		//this happens on the end of every wave
		totalScore += static_cast<unsigned int>(currentScore * multiplier);
		std::cout << "multiplier is :" << multiplier << "and score for this wave is:" << currentScore << '\n';
		//reset values
		currentScore = 0;
		multiplier = 1.0f;
		break;
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

