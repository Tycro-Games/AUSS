#include "ExplosionBullet.h"

#include "game.h"

ExplosionBullet::ExplosionBullet(Tmpl8::Sprite* sprite, Spawner* spawner, Tmpl8::vec2 pos) :
	Entity(sprite),
	spawner(spawner),
	timer(new Timer())
{
	TotalAnimation = loops * desiredTime * sprite->Frames();
	move = new MoveInstance(&this->pos);
	Init(pos);
}



ExplosionBullet::~ExplosionBullet()
{
	delete timer;
	delete move;
}

void ExplosionBullet::Init(Tmpl8::vec2 pos)
{
	SetActive(true);
	frame = 0;
	this->pos = pos;
	timer->Init(this, TotalAnimation);
	Tmpl8::Game::AddMoveable(move);
}

void ExplosionBullet::Update(float deltaTime)
{
	if (!getUpdateable())
		return;
	timer->Update(deltaTime);
	//animation
	if (currenTime < desiredTime)
		currenTime += deltaTime;
	else {
		currenTime = 0;
		frame = (frame + 1) % sprite->Frames();
	}

}

void ExplosionBullet::Render(Tmpl8::Surface* screen)
{
	if (!getRenderable())
		return;

	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));


}

void ExplosionBullet::Call()
{
	spawner->AddExplosionToPool(this);
	Tmpl8::Game::RemoveMoveable(move);
}
