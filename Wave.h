#pragma once
#include <vector>
enum  EnemyTypes
{
	Hoarder,
	Runner,
	NUMBER_OF_ENEMIES
};
struct Wave
{

	int weight = 0;
	std::vector<EnemyTypes> enemiesInWave;


};
