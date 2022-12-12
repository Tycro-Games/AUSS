#pragma once
#include "Entity.h"
#include "Timer.h"

#include "MoveInstance.h"
class Spawner;

class ExplosionBullet : public Entity
{
public:
	ExplosionBullet(Tmpl8::Sprite* sprite, Spawner* spawner, Tmpl8::vec2 pos);

	virtual ~ExplosionBullet();
	void Init(Tmpl8::vec2 pos);
	void Update(float deltaTime) override;

	void Render(Tmpl8::Surface* screen) override;
	void Call();
private:
	float TotalAnimation;
	float currenTime = 0;
	float desiredTime = .005f;//per frame
	int loops = 7;//how many animations
	Timer timer;
	Spawner* spawner;
	MoveInstance move;






};

