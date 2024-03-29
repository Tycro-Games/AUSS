#pragma once

#include "Entity.h"

#include "MoveToADirection.h"
#include "RotationVar.h"
#include "PosDir.h"
#include "Rotator.h"

class ProjectileSpawner;

class Projectile final : public Entity
{
public:
	Projectile(PosDir posDir, Tmpl8::Sprite* _sprite, ProjectileSpawner* spawner);
	~Projectile() override;

	void Init(PosDir posDir);

	void RotateToDirection();
	//getters
	Collider* getColl()
	{
		return &collider;
	}

	Moveable* getMoveable()
	{
		return &mover;
	}

	//Reflects the bullet based on the obstacle or the edges of the screen.
	void Reflect();
	//Deactivate and adds the projectile to the pool.
	void ResetBullet();

	void Update(float deltaTime) override;
	void Render(Tmpl8::Surface* screen) override;

private:
	Tmpl8::vec2 dir;
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-10, -10);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(10, 10);
	const float SPEED = 400.0f;
	const float TIME_ALIVE = 10.0f;
	RotationVar rVar = RotationVar(360 / 32.0f, 90.0f, 20.0f);

	ProjectileSpawner* spawner;
	MoveToADirection mover;
	Collider collider;
	Timer timer;
	Rotator rot;
};
