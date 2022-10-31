#include "EnemyWaveSpawner.h"
#include <iostream>

EnemyWaveSpawner::EnemyWaveSpawner()
{
	std::ifstream f("enemy_waves.json");
	input = json::parse(f);
	for (json::iterator it = input.begin(); it != input.end(); ++it) {
		std::cout << it.key() << " : " << it.value() << "\n";
	}
}

EnemyWaveSpawner::~EnemyWaveSpawner()
{
}
