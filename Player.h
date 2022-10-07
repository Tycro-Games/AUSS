#pragma once
#include "template.h"

#include "Being.h"
#include "ProjectileSpawner.h"
#include "RotationVar.h"
#include "MoveablePlayer.h"

#include "Tilemap.h"


class Player :public Being, public Callable
{
public:
	Player(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, Collider* col, MoveablePlayer*, int hp);
	~Player();
	void Render(Tmpl8::Surface* screen);
	void Update(float deltaTime);
	void Shoot(bool fire);
	void Rotate(int x, int y);
	virtual void Call()override {};
	virtual void TakeDamage(int) override;
	virtual void Die() override;

	MoveablePlayer* GetMoveable();


	ProjectileSpawner* GetSpawner();
	Tmpl8::vec2 GetPosFromStart() {
		return startingPos - pos;
	}
private:

	RotationVar rVar;
	Tmpl8::vec2* dirToFace = 0;
	Tmpl8::vec2 startingPos;
	//assets
	Tmpl8::Sprite* projectileSprite;
	//components
	MoveablePlayer* otherMovements;
	MoveablePlayer* playerMover;
	Collider* col;
	Collider colMover;
	ProjectileSpawner* spawner;
	Timer* timer;
	Tilemap* map;
	//consts
	const float TIME_TO_HIT = 2.0f;


};






