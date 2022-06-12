#pragma once
#include "Entity.h"
class Callable :public Entity
{
public:
	Callable(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos);
	virtual void Call() = 0;
	virtual  ~Callable();

private:

};


