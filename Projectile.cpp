#include "Projectile.h"



Projectile::Projectile(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, Tmpl8::vec2 dir)
	:Entity(sprite, new Tmpl8::vec2(*pos)),
	dir(dir)
{
}

Projectile::~Projectile()
{
}



void Projectile::Update(float deltaTime)
{
}

void Projectile::Render(Tmpl8::Surface* screen)
{
	sprite->Draw(screen, pos->x, pos->y);
}
