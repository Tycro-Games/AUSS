
#include "Entity.h"
using namespace Tmpl8;
using namespace std;
Entity::Entity(const filesystem::path& spritePath, unsigned int numberOfFrames, vec2 pos) :
	sprite(new Sprite(new Surface(spritePath.string().c_str()), numberOfFrames)),
	pos(pos)
{}
Entity::Entity(Sprite* sprite, vec2 pos) :
	sprite(sprite),
	pos(pos)
{}


Entity::Entity(const filesystem::path& spritePath, unsigned int numberOfFrames) :
	sprite(new Sprite(new Surface(spritePath.string().c_str()), numberOfFrames)),
	pos(vec2(0))
{
}

void Entity::Init(Tmpl8::vec2 _pos)
{
	pos = _pos;
}




Entity::~Entity()
{

}






