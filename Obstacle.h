#pragma once
#include "Moveable.h"
class Obstacle :public Moveable
{
public:
	Obstacle(Tmpl8::vec2, Collider col,size_t index);
	bool operator==(const Obstacle& ob) {
		return static_cast<int>(ob.pos.x) == static_cast<int>(pos.x) && static_cast<int>(ob.pos.y) == static_cast<int>(ob.pos.y);
	}bool operator!=(const Obstacle& ob) {
		return ob.pos.x != pos.x || ob.pos.y != ob.pos.y;
	}
	Obstacle();
	virtual ~Obstacle();

	virtual void Update(float deltaTime) override;
private:
	Tmpl8::vec2 pos;
};

