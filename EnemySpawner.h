#pragma once

#include "Spawner.h"
#include "Timer.h"
#include "Being.h"
#include "Wave.h"

#include <iostream>
class EnemyWaveSpawner;
class EnemySpawner :public Spawner, public Callable
{
public:
	~EnemySpawner();
	//pos is not a const,because it needs to be modified
	EnemySpawner(Tmpl8::vec2& pos, EnemyWaveSpawner* _enemyWave, const Tmpl8::Sprite& explosion);



	void ResetTimer(float timeToSpawn);
	void SetEnemy(EnemyTypes enemy);
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
	//getters
	const Tmpl8::vec2& GetSpawnerPos() const;
private:
	Tmpl8::vec2 pos;
	Timer timer;
	float timeToSpawn = 5.0f;
	//default the value of enemyToSpawn
	EnemyTypes enemyToSpawn = NUMBER_OF_ENEMIES;
	EnemyWaveSpawner* enemyWave = nullptr;
	MoveInstance* move;
	// Inherited via Callable
	virtual void Call() override;

};


