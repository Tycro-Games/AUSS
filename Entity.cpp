
#include "Entity.h"
using namespace Tmpl8;
Entity::Entity(Sprite* sprite, vec2 pos) :
	sprite(sprite),
	pos(pos)
{}
Entity::Entity(const std::filesystem::path& spritePath, unsigned int numberOfFrames, vec2 _pos) :
	sprite(new Sprite(new Surface(spritePath.string().c_str()), numberOfFrames)),
	pos(_pos)
{
}
Entity::Entity(Sprite* sprite) :
	sprite(sprite),
	pos(vec2(0))
{}
Entity::Entity() :
	sprite(nullptr),
	pos(vec2(0))
{}

Entity::Entity(Surface* sprite, unsigned int numberOfFrames) :
	sprite(new Sprite(sprite, numberOfFrames)),
	pos(vec2(0))
{
}

void Entity::Init(const std::filesystem::path& spritePath, unsigned int numberOfFrames, Tmpl8::vec2 _pos)
{
	sprite = new Sprite(new Surface(spritePath.string().c_str()), numberOfFrames);
	pos = _pos;
}




Entity::~Entity()
{

	delete sprite;
}






