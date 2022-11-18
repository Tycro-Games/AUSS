#include "Being.h"

Being::Being(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, int hp)
	: Entity(sprite, pos),
	hp(hp)
{}

Being::Being(const std::filesystem::path& spritePath, unsigned int numberOfFrames, Tmpl8::vec2 pos, int hp)
	: Entity(spritePath, numberOfFrames, pos),
	hp(hp)
{
}

void Being::Init(const std::filesystem::path& spritePath, unsigned int numberOfFrames, Tmpl8::vec2 _pos, int _hp)
{
	Entity::Init(spritePath, numberOfFrames, _pos);
	hp = _hp;
}



Being::~Being()
{
}
Being::Being()
{
	hp = 100;
}

void Being::TakeDamage(int dg)
{
	hp -= dg;
	if (hp <= 0) {
		Die();
	}
	//add other effects on hit
}
