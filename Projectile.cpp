#include "Projectile.h"
#include "MathFunctions.h"
#include <iostream>
#include "Spawner.h"

Projectile::Projectile(Tmpl8::vec2 pos, Tmpl8::vec2 dir, Tmpl8::Sprite* sprite)
	:Entity(sprite, new Tmpl8::vec2(pos)),
	col(new Collider(COL_MIN, COL_MAX))
{
	Init(pos, dir);



}

void Projectile::Init(Tmpl8::vec2 pos, Tmpl8::vec2 dir)
{
	isUpdateable = true;
	isRenderable = true;
	(*this->pos) = pos;
	this->dir = new Tmpl8::vec2(dir);
	timer = new Timer(this, 2.0f);
	mover = new MoveToADirection(this->pos, this->dir, col, this, SPEED);
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
	if (!isUpdateable)
		return;
	mover->Update(deltaTime);
	timer->Update(deltaTime);
}

void Projectile::Render(Tmpl8::Surface* screen)
{
	if (!isRenderable)
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, pos->x, pos->y);
	screen->Box(pos->x, pos->y, pos->x + rVar.SPRITE_OFFSET, pos->y + rVar.SPRITE_OFFSET, 0xffffff);
}

void Projectile::Call()
{
	if (timer->isFinished)
		Spawner::AddToPool(this);
	else
		Reflect();
}
