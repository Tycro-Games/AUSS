#include "Projectile.h"
#include "MathFunctions.h"
#include "ProjectileSpawner.h"

#include <iostream>


Projectile::Projectile(PosDir posDir, Tmpl8::Sprite* sprite, ProjectileSpawner* spawner)
	:Entity(sprite, posDir.pos),
	collider(COL_MIN, COL_MAX, &pos),
	spawner(spawner),
	rVar(RotationVar(360 / (static_cast<const float>(sprite->Frames() - 1)), 90.0f, 20.0f)),
	rot(&pos, &dir, &rVar, &frame, &mover)
{
	collider.type = Collider::Type::Projectile;

	mover.Init(&pos, &dir, &collider, std::bind(&Projectile::Reflect, this), SPEED);


	Init(posDir);
}
void Projectile::Init(PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;
	dir = posDir.dir;
	timer.Init(std::bind(&Projectile::ResetBullet, this), TIME_ALIVE);

	RotateToDirection();
}

Projectile::~Projectile()
{
	sprite = nullptr;//this sprite is deleted by the spawner

}

void Projectile::RotateToDirection()
{
	//rotate to the target dir
	frame = MathFunctions::RotateToDirectionFrames(rVar, dir);
}





void Projectile::Update(float deltaTime)
{
	if (!getUpdateable())
		return;

	if (collider.toDeactivate)
		ResetBullet();
	mover.Update(deltaTime);
	timer.Update(deltaTime);


}

void Projectile::Render(Tmpl8::Surface* screen)
{

	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x + collider.min.x), static_cast<int>(pos.y + collider.min.y));
#ifdef _DEBUG
	screen->Box(static_cast<int>(pos.x + collider.min.x), static_cast<int>(pos.y + collider.min.y), static_cast<int>(pos.x + collider.max.x), static_cast<int>(pos.y + collider.max.y), 0xff0000);
#endif
}

void Projectile::Reflect()
{
	if (mover.colToReflectFrom != nullptr) { //reflect on obstacle
		Collider c = *mover.colToReflectFrom;
		rot.Reflect(Collider::GetNormal(c, collider));

		mover.colToReflectFrom = nullptr;
	}
	else //reflect on screen
		rot.Reflect(Collider::GetNormalEdgeScreen(mover.nextP, collider));
}




void Projectile::ResetBullet()
{
	//trigger the enemy flag for damaging flag
	if (collider.collision)
		if (collider.collision->type == Collider::Type::Enemy)
			collider.collision->toDeactivate = true;
	collider.toDeactivate = false;
	timer.isFinished = true;
	spawner->AddProjectileToPool(this);
	spawner->SpawnExplosions(pos + collider.min);

}
