#pragma once
#include "Entity.h"
#include "MoveToADirection.h"
#include "RotationVar.h"
class Projectile :public Entity
{
public:
	Projectile(Tmpl8::vec2 pos, Tmpl8::vec2 dir, Tmpl8::Sprite* sprite);
	virtual ~Projectile();
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
private:
	Tmpl8::vec2 dir = { 0 };
	Moveable* mover;
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(0, 0);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(20, 20);
	RotationVar rVar = RotationVar(360 / 32.0f, 90.0f, 20.0f);
};


