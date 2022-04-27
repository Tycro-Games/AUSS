#pragma once
#include "surface.h"
#include "template.h"

class Entity
{
public:
	Entity(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos);
	virtual ~Entity();
protected:
	int frame = 0;
	Tmpl8::Sprite* sprite;
	Tmpl8::vec2 pos;
	virtual void Update(Tmpl8::Surface* screen);
private:

};

