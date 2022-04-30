#include "Being.h"

Being::Being(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, int hp)
	: Entity(sprite, pos),
	hp(hp)
{}

Being::~Being()
{
}

void Being::TakeDamage(int dg)
{
	hp -= dg;
	if (hp <= 0) {
		Die();
	}
	//add other effects on hit
}
