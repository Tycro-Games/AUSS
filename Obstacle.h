#pragma once
#include "Moveable.h"
class Obstacle :public Moveable
{
public:
	Obstacle(Tmpl8::vec2, Collider col);
	bool operator==(const Obstacle& ob) {
		return ob.pos.x == pos.x && ob.pos.y == ob.pos.y;
	}bool operator!=(const Obstacle& ob) {
		return ob.pos.x != pos.x || ob.pos.y != ob.pos.y;
	}
	Obstacle();
	virtual ~Obstacle();

	virtual void Update(float deltaTime) override;
private:
	Tmpl8::vec2 pos;
};

