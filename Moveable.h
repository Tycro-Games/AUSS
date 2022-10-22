#pragma once
#include "template.h"

#include "Updateable.h"
#include "Collider.h"
class Moveable :public Updateable
{
public:
	Moveable(Tmpl8::vec2* pos, Collider* col, float speed = 1.0f);
	Moveable(Tmpl8::vec2* pos);
	virtual~Moveable();
	virtual void Update(float deltaTime) = 0;
	void SetSpeed(float);
	const float GetSpeed();
	void Translation(const Tmpl8::vec2);
	Collider* getColl() const {
		return col;
	}

protected:
	Tmpl8::vec2* pos;
	Collider* col;
	float speed;


};



