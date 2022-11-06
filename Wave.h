#pragma once
enum EnemyTypes
{
	Hoarder,
	Runner,
	NUMBER_OF_ENEMIES
};
struct Wave
{

	int weight = 0;
	EnemyTypes enemiesInWave[NUMBER_OF_ENEMIES];

};
