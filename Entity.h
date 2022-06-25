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
	void SetActive() {
		isUpdateable = true;
		isRenderable = true;
	}
	Entity(Tmpl8::Sprite* sprite);

	virtual ~Entity();
protected:
	int frame = 0;
	Tmpl8::Sprite* sprite;
	Tmpl8::vec2* pos;


private:

};

