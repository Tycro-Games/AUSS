#pragma once
#include "Rotator.h"

#include "EnemySpawner.h"
class EnemyRotator :public Rotator, public Callable
{
public:
	EnemyRotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar rVar, unsigned int* frame, MoveToADirection*, EnemySpawner*);
	~EnemyRotator();
	void RotateToPlayer();
	virtual void Call() override;


private:
	EnemySpawner* spawner;

};

