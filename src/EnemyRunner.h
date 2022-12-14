#pragma once
#include "Enemy.h"
#include "Rotator.h"
class EnemyRunner final :public Enemy
{
public:
	EnemyRunner(PosDir posDir, Tmpl8::Sprite* _sprite, EnemyWaveSpawner* spawner);
	~EnemyRunner() override = default;

	void Render(Tmpl8::Surface* screen) override;
	void Update(float delta_time) override;


	Enemy* clone() override;


	void Init(PosDir) override;

private:
	void Die() override;
	void ResetEnemy() override;

	MoveToADirection mover;
	Rotator rot;
	RotationVar rVar;
	RandomNumbers randomNumbers;
	Timer deathTimer;
	//consts
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-16.5, -16.5);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(16.5, 16.5);
	const float MAX_DISTANCE_SQUARED_TO_PLAYER;
	const float SPEED = 200.0f;
	const float MIN_DEVIATION = 0.1f;
	const float MAX_DEVIATION = 0.25f;
	const float TIME_ALIVE = 10.0f;

	void Reflect();

};


