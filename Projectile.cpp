#include "Projectile.h"
#include "MathFunctions.h"
#include "ProjectileSpawner.h"

#include <iostream>


Projectile::Projectile(PosDir posDir, Tmpl8::Sprite* sprite, ProjectileSpawner* spawner)
	:Entity(sprite, posDir.pos),
	col(new Collider(COL_MIN, COL_MAX, &pos)),
	spawner(spawner),
	rVar(RotationVar(360 / (static_cast<const float>(sprite->Frames() - 1)), 90.0f, 20.0f))
{
	col->type = Collider::Projectile;
	dir = new Tmpl8::vec2();
	timer = new Timer();
	mover = new MoveToADirection(&pos, dir, col, this, SPEED);
	rot = new Rotator(&pos, dir, rVar, &frame, mover);

	Init(posDir);
}
void Projectile::Init(PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;
	(*dir) = posDir.dir;
	timer->Init(this, TIME_ALIVE);

	RotateToDirection();
}

Projectile::~Projectile()
{
	delete timer;
	delete mover;
	delete dir;
	delete col;
	delete rot;
}

void Projectile::RotateToDirection()
{
	//rotate to the target dir
	frame = MathFunctions::RotateToDirectionFrames(rVar, *dir);
}





void Projectile::Update(float deltaTime)
{
	if (!getUpdateable())
		return;

	if (col->toDeactivate)
		ResetBullet();
	mover->Update(deltaTime);
	timer->Update(deltaTime);


}

void Projectile::Render(Tmpl8::Surface* screen)
{

	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x + col->min.x), static_cast<int>(pos.y + col->min.y));
	screen->Box(static_cast<int>(pos.x + col->min.x), static_cast<int>(pos.y + col->min.y), static_cast<int>(pos.x + col->max.x), static_cast<int>(pos.y + col->max.y), 0xff0000);
}

void Projectile::Call()
{
	//delete if timer is done
	if (timer->isFinished) {

		ResetBullet();
	}
	else if (mover->colToReflectFrom != NULL) { //reflect on obstacle
		Collider c = *mover->colToReflectFrom;
		rot->Reflect(Collider::GetNormal(c, *col));

		mover->colToReflectFrom = NULL;
	}
	else //reflect on screen
		rot->Reflect(Collider::GetNormalEdgeScreen(mover->nextP, *col));
}




void Projectile::ResetBullet()
{
	//trigger the enemy flag for damaging flag
	if (col->collision)
		if (col->collision->type == Collider::Enemy)
			col->collision->toDeactivate = true;
	col->toDeactivate = false;
	timer->isFinished = true;
	spawner->AddProjectileToPool(this);
	spawner->SpawnExplosions(pos + col->min);

}
