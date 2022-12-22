#include "ExplosionBullet.h"

#include "game.h"
using namespace Tmpl8;

ExplosionBullet::ExplosionBullet(Sprite* sprite, Spawner* spawner, const vec2 pos) :
	Entity(sprite),
	spawner(spawner),
	move(&this->pos)

{
	totalAnimation = loops * desiredTime * sprite->Frames();
	ExplosionBullet::Init(pos);
}


ExplosionBullet::~ExplosionBullet()
{
	sprite = nullptr; //this sprite is deleted by the spawner
}

void ExplosionBullet::Init(const vec2 pos)
{
	SetActive(true);
	frame = 0;
	this->pos = pos;
	timer.Init(std::bind(&ExplosionBullet::ResetExplosion, this), totalAnimation);
	Game::Get().AddMoveable(&move);
}

void ExplosionBullet::Update(const float deltaTime)
{
	if (!getUpdateable())
		return;
	timer.Update(deltaTime);
	//animation
	if (currentTime < desiredTime)
		currentTime += deltaTime;
	else
	{
		currentTime = 0;
		frame = (frame + 1) % sprite->Frames();
	}
}

void ExplosionBullet::Render(Surface* screen)
{
	if (!getRenderable())
		return;

	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void ExplosionBullet::ResetExplosion()
{
	spawner->AddExplosionToPool(this);
	Game::Get().RemoveMoveable(&move);
}
