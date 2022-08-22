#pragma once
#include "template.h"

#include "Updateable.h"
#include "Collider.h"
class Moveable :public Updateable
{
public:
	Moveable(Tmpl8::vec2* pos, Collider* col, float speed = 1.0f);
	virtual~Moveable();
	virtual void Update(float deltaTime) = 0;
	void SetSpeed(float);
protected:
	Tmpl8::vec2* pos;
	Collider* col;
	float speed;


};



