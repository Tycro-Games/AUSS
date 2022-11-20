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
	collider.type = Collider::Projectile;

	mover.Init(&pos, &dir, &collider, this, SPEED);


	Init(posDir);
}
void Projectile::Init(PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;
	dir = posDir.dir;
	timer.Init(this, TIME_ALIVE);

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
	screen->Box(static_cast<int>(pos.x + collider.min.x), static_cast<int>(pos.y + collider.min.y), static_cast<int>(pos.x + collider.max.x), static_cast<int>(pos.y + collider.max.y), 0xff0000);
}

void Projectile::Call()
{
	//delete if timer is done
	if (timer.isFinished) {

		ResetBullet();
	}
	else if (mover.colToReflectFrom != NULL) { //reflect on obstacle
		Collider c = *mover.colToReflectFrom;
		rot.Reflect(Collider::GetNormal(c, collider));

		mover.colToReflectFrom = NULL;
	}
	else //reflect on screen
		rot.Reflect(Collider::GetNormalEdgeScreen(mover.nextP, collider));
}




void Projectile::ResetBullet()
{
	//trigger the enemy flag for damaging flag
	if (collider.collision)
		if (collider.collision->type == Collider::Enemy)
			collider.collision->toDeactivate = true;
	collider.toDeactivate = false;
	timer.isFinished = true;
	spawner->AddProjectileToPool(this);
	spawner->SpawnExplosions(pos + collider.min);

}
