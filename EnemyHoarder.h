#pragma once
#include "Enemy.h"
#include "RotationVar.h"
#include "Rotator.h"
#include "MoveToADirectionEnemy.h"


class EnemyHoarder :public Enemy, public Callable
{
public:
	EnemyHoarder(PosDir posDir, Tmpl8::Sprite* sprite, EnemySpawner* spawner);
	//EnemyHoarder(const Enemy& enemy);
	~EnemyHoarder();

	// Inherited via Enemy
	virtual void Update(float deltaTime) override;

	virtual void Render(Tmpl8::Surface* screen) override;
	
	void Init(PosDir posDir);
	void ResetEnemy();

	virtual void Call() override;

private:

	bool InRangeToAtack = false;
	float dist;
	Tmpl8::vec2* dir;
	float timeToRotate = 0.1f;
	//consts

	const int DG = 10;
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(0, 0);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(20, 20);
	const float TIME_TO_ATTACK = 1;

	const float SPEED = 50.0f;
	const float MAX_DISTANCE_TO_ATTACK = 400.0f;
	const float MAX_DISTANCE_TO_PLAYER = 100.0f;//this is squared so it is more efficient when comparing
	RotationVar rVar = RotationVar(360 / 16.0f, 90.0f, 20.0f);
	Rotator* rot;
	Timer* attack;

	Timer* rotate;
	MoveToADirection* mover;
	RandomNumbers randomNumbers;






	// Inherited via Enemy
	virtual void Die() override;

};

