#pragma once

#include "Callable.h"
#include "Entity.h"
#include "MoveToADirection.h"
#include "RotationVar.h"
#include "Timer.h"

#include "PosDir.h"
class Projectile :public Callable, public Entity
{
public:
	Projectile(PosDir posDir, Tmpl8::Sprite* sprite, Tmpl8::Sprite* explosionSprite);
	Projectile(const Entity* entity);


	virtual ~Projectile();
	void RotateToDirection();
	void Reflect();

	void Init(PosDir posDir);
	virtual void Call() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
private:
	Tmpl8::vec2* dir;
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(0, 0);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(20, 20);
	const float SPEED = 7.0f;
	const float TIME_ALIVE = 10.0f;
	RotationVar rVar = RotationVar(360 / 32.0f, 90.0f, 20.0f);


	MoveToADirection* mover;
	Collider* col;
	Timer* timer;



};



