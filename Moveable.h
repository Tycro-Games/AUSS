#pragma once

#include "Collider.h"
#include "Updateable.h"
class Moveable :public Updateable
{
public:
	Moveable(Tmpl8::vec2* pos, Collider* col, float speed = 1.0f);
	Moveable(Tmpl8::vec2* pos);
	Moveable();
	void Init(Tmpl8::vec2* pos, Collider* col);
	void Init(Tmpl8::vec2* pos);
	virtual~Moveable();
	virtual void Update(float deltaTime) = 0;
	void SetSpeed(float);
	const float GetSpeed();
	virtual void Translation(const Tmpl8::vec2);
	Collider* getColl() const {
		return collider;
	}

protected:
	Tmpl8::vec2* pos;
	Collider* collider;
	float speed;


};



