
#include "Entity.h"

Entity::Entity(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos) :
	sprite(sprite),
	pos(pos)
{}
Entity::Entity(Tmpl8::Sprite* sprite) :
	sprite(sprite),
	pos(new Tmpl8::vec2(0))
{}

Entity::Entity(Tmpl8::Surface* sprite, unsigned int numberOfFrames) :
	sprite(new Tmpl8::Sprite(sprite, numberOfFrames)),
	pos(new Tmpl8::vec2(0))
{
}




Entity::~Entity()
{

	delete sprite;
	delete pos;
}






