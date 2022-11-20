#pragma once
#include "Rotator.h"

#include "EnemyWaveSpawner.h"
class EnemyWaveSpawner;
class EnemyRotator :public Rotator, public Callable
{
public:
	EnemyRotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection* mover, EnemyWaveSpawner* spawn);
	EnemyRotator();
	void Init(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection* mover, EnemyWaveSpawner* spawn);
	~EnemyRotator();
	void RotateToPlayer();
	virtual void Call() override;


private:
	EnemyWaveSpawner* spawner;

};

