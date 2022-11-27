#pragma once
#include "Enemy.h"
#include "Rotator.h"
class EnemyRunner :public Enemy, public Callable
{
public:
	EnemyRunner(PosDir posDir, Tmpl8::Sprite* sprite, EnemyWaveSpawner* spawner);
	~EnemyRunner() = default;

	void Render(Tmpl8::Surface* screen) override;
	void Update(float deltaTime) override;

	// Inherited via Enemy
	virtual void Die() override;

	virtual Enemy* clone() override;


	virtual void Init(PosDir) override;

	virtual void ResetEnemy() override;
private:

	MoveToADirection mover;
	Rotator rot;
	RotationVar rVar;
	RandomNumbers randomNumbers;

	//consts
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-10, -10);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(10, 10);
	const float MAX_DISTANCE_SQUARED_TO_PLAYER;
	const float SPEED = 200.0f;
	const float MIN_DEVIATION = 0.1f;
	const float MAX_DEVIATION = 1.0f;

	// Inherited via Callable
	void Call() override;

};


