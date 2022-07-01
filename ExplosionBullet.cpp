#include "ExplosionBullet.h"

#include "Spawner.h"

ExplosionBullet::ExplosionBullet(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos) :
	Entity(sprite)
{
	Init(*pos);
}



ExplosionBullet::~ExplosionBullet()
{
	delete timer;
}

void ExplosionBullet::Init(Tmpl8::vec2 pos)
{
	(*this->pos) = pos;
	timer = new Timer(this, 5.0f);
}

void ExplosionBullet::Update(float deltaTime)
{
	timer->Update(deltaTime);
}

void ExplosionBullet::Render(Tmpl8::Surface* screen)
{

	sprite->Draw(screen, pos->x, pos->y);
}

void ExplosionBullet::Call()
{
	Spawner::AddExplosionToPool(this);
}
