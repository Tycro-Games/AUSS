#pragma once

#include "Entity.h"

#include "MoveToADirection.h"
#include "RotationVar.h"
#include "PosDir.h"
class ProjectileSpawner;
class Projectile :public Callable, public Entity
{

public:
	Projectile(PosDir posDir, Tmpl8::Sprite* sprite, ProjectileSpawner* spawner);

	virtual ~Projectile();
	void RotateToDirection();
	void Reflect(Tmpl8::vec2 normal);

	void Init(PosDir posDir);
	Collider* getColl() const {
		return col;
	}
	Moveable* getMoveable() const {
		return mover;
	}
	virtual void Call() override;
	void ResetBullet();
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;

private:
	Tmpl8::vec2* dir;
	const int DG = 10;
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-10, -10);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(10, 10);
	const float SPEED = 250.0f;
	const float TIME_ALIVE = 10.0f;
	RotationVar rVar = RotationVar(360 / 32.0f, 90.0f, 20.0f);

	ProjectileSpawner* spawner;
	MoveToADirection* mover;
	Collider* col;
	Timer* timer;



};



