#pragma once
#include "surface.h"
#include "template.h"
//interfaces
#include "Updateable.h"
#include "Renderable.h"
class Entity :public Updateable, public Renderable
{
public:
	Entity(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos);
	Entity();
	virtual ~Entity();
protected:
	int frame = 0;
	Tmpl8::Sprite* sprite;
	Tmpl8::vec2* pos;

private:

};

