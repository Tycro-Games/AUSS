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
	//timers
	Timer rotate;

	MoveToADirection mover;
	Rotator rot;
	RotationVar rVar = RotationVar(360 / 16.0f, 90.0f, 20.0f);

	//consts
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-10, -10);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(10, 10);


	// Inherited via Callable
	void Call() override;

};


