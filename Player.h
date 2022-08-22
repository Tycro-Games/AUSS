#pragma once
#include "template.h"

#include "Being.h"
#include "ProjectileSpawner.h"
#include "RotationVar.h"
#include "MoveablePlayer.h"



class Player :public Being, public Callable
{
public:
	Player(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, Collider* col, int hp);
	~Player();
	void Render(Tmpl8::Surface* screen);
	void Update(float deltaTime);
	void Shoot(bool fire);
	void Rotate(float x, float y);
	virtual void Call()override {};
	virtual void TakeDamage(int) override;
	virtual void Die() override;

	MoveablePlayer* GetMoveable();

	ProjectileSpawner* GetSpawner();

private:
	RotationVar rVar = RotationVar();
	Tmpl8::vec2* dirToFace = 0;
	//assets
	Tmpl8::Sprite* projectileSprite;
	Tmpl8::Sprite* explosionSprite;
	//components
	MoveablePlayer* mover;
	Collider* col;
	ProjectileSpawner* spawner;
	Timer* timer;
	//consts
	const float TIME_TO_HIT = 2.0f;


};






