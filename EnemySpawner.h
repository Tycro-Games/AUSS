#pragma once

#include "Spawner.h"
#include "Timer.h"
#include "Being.h"

#include <iostream>
#include "EnemyWaveSpawner.h"
#include "Enemy.h"
class Enemy;
class EnemyWaveSpawner;
class EnemySpawner :public Spawner, public Callable
{
public:
	~EnemySpawner();
	EnemySpawner(Tmpl8::vec2* pos, EnemyWaveSpawner*, Tmpl8::Sprite*);



	void PlayerTakesDamage(Enemy* enemy);
	void ResetTimer(float timeToSpawn);
	Tmpl8::vec2 GetPlayerPos();
	void SetEnemy(EnemyTypes enemy);
	bool IsEnemy(Collider*);
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
private:
	Timer* timer;
	float timeToSpawn = 5.0f;
	EnemyTypes enemyToSpawn = NUMBER_OF_ENEMIES;
	EnemyWaveSpawner* enemyWave = nullptr;

	// Inherited via Callable
	virtual void Call() override;

};


