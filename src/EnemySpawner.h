#pragma once

#include "Spawner.h"
#include "Being.h"
#include "Wave.h"

class EnemyWaveSpawner;
class EnemySpawner :public Spawner
{
public:
	~EnemySpawner() override = default;
	//posObs is not a const,because it needs to be modified
	EnemySpawner(Tmpl8::vec2 _pos, Tmpl8::Sprite* explosion);

	void SetEnemy(EnemyTypes enemy);
	void Update(float deltaTime) override;
	void Render(Tmpl8::Surface* screen) override;
	//getters
	const Tmpl8::vec2& GetSpawnerPos() const;
private:
	Tmpl8::vec2 pos;
	//default the value of enemyToSpawn
	EnemyTypes enemyToSpawn = NUMBER_OF_ENEMIES;
	MoveInstance move;


};


