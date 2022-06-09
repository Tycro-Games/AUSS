#pragma once
#include "Entity.h"
#include "Moveable.h"
class Projectile :public Entity
{
public:
	Projectile(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, Tmpl8::vec2 dir);
	virtual ~Projectile();
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
private:
	Tmpl8::vec2 dir = { 0 };
	//Moveable* mover;

};


