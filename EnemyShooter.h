#pragma once
#include "Enemy.h"
#include "Rotator.h"
class EnemyShooter : public Enemy, public Callable
{
public:
	EnemyShooter(PosDir posDir, Tmpl8::Sprite* sprite, EnemyWaveSpawner* _spawner);
	~EnemyShooter() = default;

	// Inherited via Enemy
	void Update(float deltaTime) override;

	void Render(Tmpl8::Surface* screen) override;


	Enemy* clone() override;

	void Init(PosDir) override;

private:
	bool canMove = false;
	void Die() override;
	void ResetEnemy() override;
	//consts
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-10, -10);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(10, 10);
	const float MAX_DISTANCE_SQUARED_TO_PLAYER;
	const float MOVE_INTERVAL = 0.5f;
	const float STOP_INTERVAL = 3.0f;
	const float MIN_DEVIATION = 0.1f;
	const float MAX_DEVIATION = 1.0f;
	//components
	MoveToADirection mover;
	Rotator rot;
	RotationVar rVar;
	RandomNumbers randomNumbers;
	Timer timerToStop;
	Timer timerToMove;

	// Inherited via Callable
	void Call() override;

};
