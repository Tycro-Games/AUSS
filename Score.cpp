#include "Score.h"




void Score::onNotify(int points, EventType event)
{
	switch (event)
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

