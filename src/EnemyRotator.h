#pragma once
#include "Rotator.h"

class EnemyRotator :public Rotator
{
public:
	EnemyRotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection* mover);
	EnemyRotator();
	void Init(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection* mover);
	~EnemyRotator() = default;
	void RotateToPlayer();


private:

};
