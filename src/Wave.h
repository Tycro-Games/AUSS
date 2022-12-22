#pragma once
#include <vector>

enum class EnemyTypes //ADD CLASS here
{
	Hoarder,
	Runner,
	Shooter,
	Shielder,
	NUMBER_OF_ENEMIES
};

struct Wave
{
	unsigned int weight = 0;
	std::vector<EnemyTypes> enemiesInWave;
};
