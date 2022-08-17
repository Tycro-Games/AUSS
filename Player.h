#pragma once
#include "template.h"

#include "Being.h"
#include "ProjectileSpawner.h"
#include "RotationVar.h"
#include "MoveablePlayer.h"



class Player :public Being
{
public:
	Player(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, Collider* col, int hp);
	~Player();
	void Render(Tmpl8::Surface* screen);
	void Update(float deltaTime);
	void Shoot(bool fire);
	void Rotate(float x, float y);
	MoveablePlayer* GetMoveable();

	ProjectileSpawner* GetSpawner();

private:
	RotationVar rVar = RotationVar();
	Tmpl8::vec2* dirToFace = 0;
	Tmpl8::Sprite* projectileSprite;
	Tmpl8::Sprite* explosionSprite;
	MoveablePlayer* mover;
	Collider* col;
	ProjectileSpawner* spawner;

};






