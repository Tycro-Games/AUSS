#pragma once
#include "Entity.h"
#include "Timer.h"

#include <iostream>

class EnemySpawner :public Entity, public Callable
{
public:
	EnemySpawner(Tmpl8::Sprite*, Tmpl8::vec2*);
	~EnemySpawner();

	// Inherited via Entity
	virtual void Update(float deltaTime) override;

	virtual void Render(Tmpl8::Surface* screen) override;
private:
	Timer* timer;
	float timeToSpawn = 5.0f;



	// Inherited via Callable
	virtual void Call() override;

};


