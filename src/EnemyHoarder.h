#pragma once
#include "EnemyRotator.h"
#include "Enemy.h"



class EnemyHoarder :public Enemy
{
public:
	EnemyHoarder(PosDir posDir, Tmpl8::Sprite* _sprite, EnemyWaveSpawner* _spawner);

	~EnemyHoarder() = default;

	void Init(PosDir posDir) override;
	void Update(float deltaTime) override;

	void Render(Tmpl8::Surface* screen) override;


	Enemy* clone() override;
private:
	void Reflect();
	void ResetEnemy() override;
	void Die() override;
	void AtackPlayer();

	bool InRangeToAtack = false;
	//consts
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-16.5, -16.5);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(16.5, 16.5);
	const float TIME_TO_ATTACK = 0.25f;

	const float SPEED = 50.0f;
	const float MAX_DISTANCE_SQUARED_TO_PLAYER;
	//timers
	Timer attack;
	Timer rotate;

	MoveToADirection mover;
	RandomNumbers randomNumbers;

	RotationVar rVar;

	EnemyRotator rot;
};

