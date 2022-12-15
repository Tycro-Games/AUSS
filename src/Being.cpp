#include "Being.h"
using namespace Tmpl8;
using namespace std;

Being::Being(const std::filesystem::path& spritePath, const unsigned int numberOfFrames, const vec2 pos, const int hp)
	: Entity(spritePath, numberOfFrames, pos),
	hp(hp)
{
}
Being::Being(Sprite* sprite, const vec2 pos, const int hp)
	: Entity(sprite, pos),
	hp(hp)
{}
void Being::Init(const vec2 _pos, const int _hp)
{
	Entity::Init(_pos);
	hp = _hp;
}






void Being::TakeDamage(const unsigned int dg)
{
	hp -= dg;
	if (hp <= 0) {
		Die();
	}
	//add other effects on hit
}

int Being::GetHp() const
{
	return hp;
}
