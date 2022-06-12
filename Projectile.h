#pragma once
#include "Callable.h"
#include "MoveToADirection.h"
#include "RotationVar.h"
#include "Timer.h"
#include "Spawner.h"
class Projectile :public Callable
{
public:
	Projectile(Tmpl8::vec2 pos, Tmpl8::vec2 dir, Tmpl8::Sprite* sprite, Spawner* spawn);
	virtual ~Projectile();
	void Call();
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
private:
	Tmpl8::vec2 dir = { 0 };
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(0, 0);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(20, 20);
	RotationVar rVar = RotationVar(360 / 32.0f, 90.0f, 20.0f);

	Spawner* spawner;
	Moveable* mover;
	Timer* timer;
};



