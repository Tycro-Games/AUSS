#pragma once
#include "Moveable.h"
class Obstacle :public Moveable
{
public:
	Obstacle(Tmpl8::vec2, const Collider& _collider);
	Obstacle();
	~Obstacle() override;
	void Update(float deltaTime) override;
	void Init(Tmpl8::vec2, const Collider& col);
	bool operator==(const Obstacle& ob) const;

	bool operator!=(const Obstacle& ob) const;

private:
	Tmpl8::vec2 posObs;
	Collider obsCollider;
};

