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
	~EnemySpawner();

	EnemySpawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Being* player, Tmpl8::Sprite* toSpawn, Tmpl8::Sprite* explosion);

	void AddEnemyToPool(Enemy* enemy);
	void CreateMoreEnemies();

	void PlayerTakesDamage(Enemy* enemy);

	Tmpl8::vec2 GetPlayerPos();
	bool IsEnemy(Collider*);
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
private:
	Timer* timer;
	float timeToSpawn = 1.0f;
	Being* player;
	pool<Enemy*> poolOfEnemies;
	//assets for enemies
	Tmpl8::Sprite* enemySprite;


	// Inherited via Callable
	virtual void Call() override;

};


