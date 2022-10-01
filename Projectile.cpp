#include "Projectile.h"
#include "MathFunctions.h"
#include <iostream>
#include "ProjectileSpawner.h"


Projectile::Projectile(PosDir posDir, Tmpl8::Sprite* sprite, ProjectileSpawner* spawner)
	:Entity(sprite,  posDir.pos),
	col(new Collider(COL_MIN, COL_MAX, &pos)),
	spawner(spawner)
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
	sprite = nullptr;//so it does not get deleted twice by entity
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

	//marked by collision
	if (col->toDeactivate)
		ResetBullet();
}

void Projectile::Render(Tmpl8::Surface* screen)
{

	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
	//screen->Box(pos.x, pos.y, pos.x + rVar.SPRITE_OFFSET, pos.y + rVar.SPRITE_OFFSET, 0xffffff);
}

void Projectile::Call()
{
	//delete if timer is done
	if (timer->isFinished) {

		ResetBullet();
	}
	else //collides with screen
		Reflect();
}

void Projectile::ResetBullet()
{

	col->toDeactivate = false;
	timer->isFinished = true;
	spawner->AddProjectileToPool(this);
	spawner->SpawnExplosions(pos);
}
