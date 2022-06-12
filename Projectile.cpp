#include "Projectile.h"
#include "MathFunctions.h"



Projectile::Projectile(Tmpl8::vec2 pos, Tmpl8::vec2 dir, Tmpl8::Sprite* sprite)
	:Entity(sprite, new Tmpl8::vec2(pos)),
	dir(dir)
{

	mover = new MoveToADirection(this->pos, dir, new Collider(COL_MIN, COL_MAX));

	//rotate to the target dir
	float angle = MathFunctions::GetDirInAngles(dir);
	angle += rVar.OFFSET_SPRITE;
	angle = fmod(angle, 360);
	frame = angle / rVar.ANGLE_SIZE;
}

Projectile::~Projectile()
{
	sprite = nullptr;
	delete mover;
}



void Projectile::Update(float deltaTime)
{
	mover->Update(deltaTime);
}

void Projectile::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	sprite->Draw(screen, pos->x, pos->y);
	//screen->Box(pos->x, pos->y, pos->x + rVar.SPRITE_OFFSET, pos->y + rVar.SPRITE_OFFSET, 0xffffff);
}
