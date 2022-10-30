#include "ParallaxProp.h"


ParallaxProp::ParallaxProp(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, float speed)
	:Entity(sprite, pos)
{
	move = new MoveInstance(&this->pos, speed);

}

ParallaxProp::~ParallaxProp()
{
	delete move;
}

void ParallaxProp::Update(float deltaTime)
{

}

void ParallaxProp::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
}

Moveable* ParallaxProp::getMover()const
{
	return move;
}
