#pragma once
#include "RotationVar.h"
#include "EnemyRotator.h"
#include "Enemy.h"



class EnemyHoarder :public Enemy, public Callable
{
public:
	EnemyHoarder(PosDir posDir, Tmpl8::Sprite* sprite, EnemyWaveSpawner* spawner);

	~EnemyHoarder();

	// Inherited via Enemy
	virtual void Init(PosDir posDir) override;
	void Update(float deltaTime) override;

	void Render(Tmpl8::Surface* screen) override;

	virtual void ResetEnemy() override;

	void Call() override;

	virtual Enemy* clone() override;
private:
	//movement
	bool ToMove = false;
	bool InRangeToAtack = false;
	float dist;
	float timeToRotate = 0.1f;

	//consts
	const int DG_TO_TAKE = 25;
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-10, -10);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(10, 10);
	const float TIME_TO_ATTACK = 0.25f;

	const float SPEED = 50.0f;
	const float MAX_DISTANCE_TO_ATTACK = 400.0f;
	const float MAX_DISTANCE_TO_PLAYER = 100.0f;//this is squared so it is more efficient when comparing
	Timer attack;

	Timer rotate;
	MoveToADirection mover;
	RandomNumbers randomNumbers;

	RotationVar rVar = RotationVar(360 / 16.0f, 90.0f, 20.0f);

	EnemyRotator rot;
	// Inherited via Enemy
	virtual void Die() override;



};

