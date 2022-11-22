#include "Being.h"
using namespace Tmpl8;
using namespace std;

Being::Being(const std::filesystem::path& spritePath, unsigned int numberOfFrames, Tmpl8::vec2 pos, int hp)
	: Entity(spritePath, numberOfFrames, pos),
	hp(hp)
{
}
Being::Being(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, int hp)
	: Entity(sprite, pos),
	hp(hp)
{}
void Being::Init(vec2 _pos, int _hp)
{
	Entity::Init(_pos);
	hp = _hp;
}






void Being::TakeDamage(int dg)
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
