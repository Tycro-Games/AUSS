#pragma once
#include "Rotator.h"

class EnemyRotator :public Rotator, public Callable
{
public:
	EnemyRotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection* mover);
	EnemyRotator();
	void Init(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection* mover);
	~EnemyRotator();
	void RotateToPlayer();
	void Call() override;


private:

};

