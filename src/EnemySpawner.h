#pragma once

#include "Spawner.h"
#include "Timer.h"
#include "Being.h"
#include "Wave.h"

#include <iostream>
class EnemyWaveSpawner;
class EnemySpawner :public Spawner
{
public:
	~EnemySpawner();
	//pos is not a const,because it needs to be modified
	EnemySpawner(Tmpl8::vec2& pos, EnemyWaveSpawner* _enemyWave, Tmpl8::Sprite* explosion);

	void SetEnemy(EnemyTypes enemy);
	void Update(float deltaTime) override;
	void Render(Tmpl8::Surface* screen) override;
	//getters
	const Tmpl8::vec2& GetSpawnerPos() const;
private:
	Tmpl8::vec2 pos;
	float timeToSpawn = 5.0f;
	//default the value of enemyToSpawn
	EnemyTypes enemyToSpawn = NUMBER_OF_ENEMIES;
	EnemyWaveSpawner* enemyWave = nullptr;
	MoveInstance move;


};


