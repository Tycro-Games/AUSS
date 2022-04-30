#pragma once
#include "surface.h"
#include "template.h"

#include "Updateable.h"

class Entity :public Updateable
{
public:
	Entity(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos);
	virtual ~Entity();
protected:
	int frame = 0;
	Tmpl8::Sprite* sprite;
	Tmpl8::vec2 pos;

private:

};

