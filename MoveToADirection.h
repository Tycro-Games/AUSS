#pragma once
#include "Moveable.h"

class MoveToADirection :public Moveable
{
public:
	MoveToADirection(Tmpl8::vec2* pos, Tmpl8::vec2 dir, Collider* col, float speed = 2.0f);
	virtual void Update(float deltaTime)override;
	virtual ~MoveToADirection();

private:
	Tmpl8::vec2 dir;
};


