#pragma once
#include <vector>
enum  EnemyTypes
{
	Hoarder,
	Runner,
	Shooter,
	NUMBER_OF_ENEMIES
};
struct Wave
{

	int weight = 0;
	std::vector<EnemyTypes> enemiesInWave;


};
