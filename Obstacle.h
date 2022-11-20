#pragma once
#include "Moveable.h"
class Obstacle :public Moveable
{
public:
	Obstacle(const Tmpl8::vec2, const Collider& col);
	Obstacle();
	virtual ~Obstacle() = default;
	void Update(float deltaTime) override;
	void Init(const Tmpl8::vec2, const Collider& col);
	bool operator==(const Obstacle& ob) {
		return static_cast<int>(ob.pos.x) == static_cast<int>(pos.x) && static_cast<int>(ob.pos.y) == static_cast<int>(ob.pos.y);
	}bool operator!=(const Obstacle& ob) {
		return ob.pos.x != pos.x || ob.pos.y != ob.pos.y;
	}
private:
	Tmpl8::vec2 pos;
	Collider obsCollider;
};

