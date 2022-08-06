#include "Projectile.h"
#include "MathFunctions.h"
#include <iostream>
#include "Spawner.h"


Projectile::Projectile(PosDir posDir, Tmpl8::Sprite* sprite, Spawner* spawner)
	:Entity(sprite, new Tmpl8::vec2(posDir.pos)),
	col(new Collider(COL_MIN, COL_MAX)),
	spawner(spawner)
{
	dir = new Tmpl8::vec2();
	timer = new Timer();
	mover = new MoveToADirection(this->pos, this->dir, col, this, SPEED);
	Init(posDir);
}
void Projectile::Init(PosDir posDir)
{
	SetActive(true);
	(*pos) = posDir.pos;
	(*dir) = posDir.dir;
	timer->Init(this, TIME_ALIVE);

	RotateToDirection();
}

Projectile::~Projectile()
{
	sprite = nullptr;
	delete timer;
	delete mover;
}

void Projectile::RotateToDirection()
{
	//rotate to the target dir
	frame = fmod(MathFunctions::GetDirInAnglesPos(*dir) + rVar.OFFSET_SPRITE, 360) / rVar.ANGLE_SIZE;
}

void Projectile::Reflect()
{

	Tmpl8::vec2 normal = Collider::GetNormalEdgeScreen(mover->nextP, *col);

	mover->OppositeDirection(normal);
	RotateToDirection();
}



void Projectile::Update(float deltaTime)
{
	if (!getUpdateable())
		return;
	mover->Update(deltaTime);
	timer->Update(deltaTime);
}

void Projectile::Render(Tmpl8::Surface* screen)
{

	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, pos->x, pos->y);
	screen->Box(pos->x, pos->y, pos->x + rVar.SPRITE_OFFSET, pos->y + rVar.SPRITE_OFFSET, 0xffffff);
}

void Projectile::Call()
{
	if (timer->isFinished) {

		ResetBullet();
	}
	else
		Reflect();
}

void Projectile::ResetBullet()
{
	timer->isFinished = true;
	spawner->AddProjectileToPool(this);
	spawner->SpawnExplosions(*pos);
}
