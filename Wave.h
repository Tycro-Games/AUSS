#pragma once
#include "dynamic_array.h"
enum EnemyTypes
{
	Hoarder,
	Runner,
	NUMBER_OF_ENEMIES
};
struct Wave
{

	int weight = 0;
	dynamic_array<EnemyTypes> enemiesInWave;


};
