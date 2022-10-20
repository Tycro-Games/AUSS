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
		//obstacle is a collider with the pivot in the top left
		//calculate normal based on https://gamedev.stackexchange.com/questions/136073/how-does-one-calculate-the-surface-normal-in-2d-collisions
		
		Collider c = *mover->colToReflectFrom;

		Tmpl8::vec2 midPoint = (*c.pos) + Tmpl8::vec2(c.max.x / 2, c.max.y / 2);

		Tmpl8::vec2 dist = pos - midPoint;

		float ex = c.max.x / 2.0f;
		float ey = c.max.y / 2.0f;
		Tmpl8::vec2 BottomLeft = *c.pos + Tmpl8::vec2(0, c.max.y);
		Tmpl8::vec2 BottomRight = *c.pos + c.max;

		Tmpl8::vec2 ux = (BottomRight - BottomLeft).normalized();
		Tmpl8::vec2 uy = (*c.pos - BottomLeft).normalized();

		float distX = dist.dot(ux);
		float distY = dist.dot(uy);

		if (distX > ex)distX = ex;
		else if (distX < -ex)distX = -ex;

		if (distY > ey)distY = ey;
		else if (distY < -ey)distY = -ey;

		Tmpl8::vec2 hitPoint = midPoint + ux * distX + uy * distY;

		Tmpl8::vec2 norm = (pos - hitPoint).normalized();
		Reflect(norm);

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
