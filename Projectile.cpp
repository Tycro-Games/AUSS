#include "Projectile.h"
#include "MathFunctions.h"
#include <iostream>
#include "ProjectileSpawner.h"


Projectile::Projectile(PosDir posDir, Tmpl8::Sprite* sprite, ProjectileSpawner* spawner)
	:Entity(sprite, posDir.pos),
	col(new Collider(COL_MIN, COL_MAX, &pos)),
	spawner(spawner),
	rVar(RotationVar(360 / (static_cast<const float>(sprite->Frames() - 1)), 90.0f, 20.0f))
{
	dir = new Tmpl8::vec2();
	timer = new Timer();
	mover = new MoveToADirection(&pos, dir, col, this, SPEED);
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
	sprite = nullptr;//so it does not get deleted twice 
	delete timer;
	delete mover;
	delete dir;
	delete col;
}

void Projectile::RotateToDirection()
{
	//rotate to the target dir
	frame = MathFunctions::RotateToDirectionFrames(rVar, *dir);
}

void Projectile::Reflect(const Tmpl8::vec2 normal)
{

	mover->OppositeDirection(normal);
	RotateToDirection();
}



void Projectile::Update(float deltaTime)
{
	if (!getUpdateable())
		return;

	mover->Update(deltaTime);
	timer->Update(deltaTime);


	if (col->toDeactivate)
		ResetBullet();
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
	else if (mover->colToReflectFrom != NULL) {
		Collider c = *mover->colToReflectFrom;


		if (pos.x + col->min.x < c.min.x + c.pos->x || pos.x + col->max.x > c.max.x + c.pos->x)
			Reflect(Tmpl8::vec2(1, 0));
		if (pos.y + col->min.y < c.min.y + c.pos->y || pos.y + col->max.y > c.max.y + c.pos->y)
			Reflect(Tmpl8::vec2(0, 1));
		mover->colToReflectFrom = NULL;
	}
	else
		Reflect(Collider::GetNormalEdgeScreen(mover->nextP, *col));
}

void Projectile::ResetBullet()
{

	col->toDeactivate = false;
	timer->isFinished = true;
	spawner->AddProjectileToPool(this);
	spawner->SpawnExplosions(pos + col->min);
}
