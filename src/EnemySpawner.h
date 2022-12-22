#pragma once

#include "Spawner.h"
#include "Being.h"
#include "Wave.h"

class EnemyWaveSpawner;

class EnemySpawner : public Spawner
{
public:
	EnemySpawner(Tmpl8::vec2 _pos, Tmpl8::Sprite* explosion);
	~EnemySpawner() override = default;

	void Update(float deltaTime) override;
	void Render(Tmpl8::Surface* screen) override;

	//getters
	const Tmpl8::vec2& GetSpawnerPos() const;

private:
	Tmpl8::vec2 pos;
	MoveInstance move;
};
