#pragma once
#include "Entity.h"
class Being : public Entity {
public:
	Being(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, int hp);
	virtual ~Being();
	void TakeDamage(int dg);
protected:
	int hp;
	void Die() {

	}

private:
};
