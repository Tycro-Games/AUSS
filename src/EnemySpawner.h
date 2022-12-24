#pragma once

#include "Spawner.h"
#include "Being.h"

class EnemyWaveSpawner;

class EnemySpawner
{
public:
	EnemySpawner(Tmpl8::vec2 _pos);
	~EnemySpawner() = default;

	//getters
	const Tmpl8::vec2& GetSpawnerPos() const;

private:
	Tmpl8::vec2 pos;
	MoveInstance move;
};
