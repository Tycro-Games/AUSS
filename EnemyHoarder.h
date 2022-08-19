#pragma once
#include "Enemy.h"
#include "MoveToADirection.h"
#include "RotationVar.h"



class EnemyHoarder :public Enemy, public Callable
{
public:
	EnemyHoarder(PosDir posDir, Tmpl8::Sprite* sprite, EnemySpawner* spawner);
	~EnemyHoarder();

	// Inherited via Enemy
	virtual void Update(float deltaTime) override;

	virtual void Render(Tmpl8::Surface* screen) override;
	void RotateToDirection();
	void Init(PosDir posDir);
	void ResetEnemy();
	bool toDeactivate = false;
	virtual void Call() override;

private:


	Tmpl8::vec2* dir;
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(0, 0);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(20, 20);
	const float SPEED = 50.0f;

	RotationVar rVar = RotationVar(360 / 16.0f, 90.0f, 20.0f);


	MoveToADirection* mover;
	Collider* col;





};

