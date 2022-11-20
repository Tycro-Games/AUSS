#pragma once
#include "Enemy.h"
class EnemyRunner :public Enemy
{
public:
	EnemyRunner(PosDir posDir, Tmpl8::Sprite* sprite, EnemyWaveSpawner* spawner);
	~EnemyRunner();

	void Render(Tmpl8::Surface* screen) override;
	void Update(float deltaTime) override;

	// Inherited via Enemy
	virtual void Die() override;

	virtual Enemy* clone() override;


	virtual void Init(PosDir) override;

	virtual void ResetEnemy() override;
private:
	MoveInstance mover;


};


