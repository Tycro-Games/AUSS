#pragma once
#include "EnemySpawner.h"
#include "Callable.h"


class Rotator : public Callable
{
public:
	Rotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar rVar, int* frame, MoveToADirection*, EnemySpawner*);

	void RotateToDirection(Tmpl8::vec2);
	static bool CheckVec2(const Tmpl8::vec2& Pos);
	void Reflect();
	~Rotator() {};
	virtual void Call() override;
	void RotateToPlayer();
private:
	int* frame;
	Tmpl8::vec2* pos;
	Tmpl8::vec2* dir;
	RotationVar rVar;
	MoveToADirection* mover;
	EnemySpawner* spawner;

};

