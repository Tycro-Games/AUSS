#pragma once

#include "Spawner.h"
#include "Timer.h"
#include "Enemy.h"

#include <iostream>
#include "Being.h"
class Enemy;
class EnemySpawner :public Spawner, public Callable
{
public:
	EnemySpawner(Tmpl8::vec2*, Tmpl8::vec2*, Being*, Tmpl8::Sprite*);
	~EnemySpawner();

	void AddEnemyToPool(Enemy* enemy);

	void CreateMoreEnemies();
	virtual void Update(float deltaTime) override;
	Tmpl8::vec2 GetPlayerPos();
	virtual void Render(Tmpl8::Surface* screen) override;
private:
	Timer* timer;
	float timeToSpawn = 5.0f;
	Being* player;
	pool<Enemy*> poolOfEnemies;
	//assets for enemies
	Tmpl8::Sprite* enemySprite;


	// Inherited via Callable
	virtual void Call() override;

};


