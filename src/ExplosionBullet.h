#pragma once
#include "Entity.h"
#include "Timer.h"

#include "MoveInstance.h"
class Spawner;

class ExplosionBullet : public Entity
{
public:
	ExplosionBullet(Tmpl8::Sprite* sprite, Spawner* spawner, Tmpl8::vec2 pos);
	~ExplosionBullet() override;

	void Init(Tmpl8::vec2 pos) override;

	void Update(float deltaTime) override;
	void Render(Tmpl8::Surface* screen) override;
	//Adds the explosion to the pool and disables it.
	void ResetExplosion();

private:
	float totalAnimation;
	float currentTime = 0;
	float desiredTime = .005f; //per frame
	int loops = 7; //how many animations
	Timer timer;
	Spawner* spawner;
	MoveInstance move;
};
