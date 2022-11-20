#include "ExplosionBullet.h"

#include "game.h"
using namespace Tmpl8;
ExplosionBullet::ExplosionBullet(Sprite* sprite, Spawner* spawner, vec2 pos) :
	Entity(sprite),
	spawner(spawner),
	move(&this->pos)

{
	TotalAnimation = loops * desiredTime * sprite->Frames();
	Init(pos);
}



ExplosionBullet::~ExplosionBullet()
{
	sprite = nullptr;//this sprite is deleted by the spawner
}

void ExplosionBullet::Init(vec2 pos)
{
	SetActive(true);
	frame = 0;
	this->pos = pos;
	timer.Init(this, TotalAnimation);
	Game::Get().AddMoveable(&move);
}

void ExplosionBullet::Update(float deltaTime)
{
	if (!getUpdateable())
		return;
	timer.Update(deltaTime);
	//animation
	if (currenTime < desiredTime)
		currenTime += deltaTime;
	else {
		currenTime = 0;
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

void ExplosionBullet::Call()
{
	spawner->AddExplosionToPool(this);
	Game::Get().RemoveMoveable(&move);
}
