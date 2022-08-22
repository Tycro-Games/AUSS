#pragma once
#include "EnemySpawner.h"
#include "Callable.h"


class Rotator : public Callable
{
public:
	Rotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar rVar, int& frame, EnemySpawner*);

	void RotateToDirection(Tmpl8::vec2);
	~Rotator() {};
	virtual void Call() override;
private:
	int* frame;
	Tmpl8::vec2* pos;
	Tmpl8::vec2* dir;
	RotationVar rVar;
	EnemySpawner* spawner;

};

