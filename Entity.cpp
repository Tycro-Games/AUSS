
#include "Entity.h"

Entity::Entity(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos) :
	sprite(sprite),
	pos(pos)
{}

Entity::Entity()
{
	sprite = 0;
	pos = 0;
}



Entity::~Entity()
{
	if (sprite) {
		delete sprite;
		sprite = nullptr;
	}
	delete pos;
}




