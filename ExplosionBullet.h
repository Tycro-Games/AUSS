#pragma once
#include "Entity.h"
#include "Timer.h"

#include "MoveInstance.h"
class Spawner;

class ExplosionBullet : public Entity, public Callable
{
public:
	ExplosionBullet(Tmpl8::Sprite* sprite, Spawner* spawner, Tmpl8::vec2 pos);

	virtual ~ExplosionBullet();
	void Init(Tmpl8::vec2 pos);
	virtual void Update(float deltaTime) override;

	virtual void Render(Tmpl8::Surface* screen) override;
	virtual void Call() override;
private:
	float TotalAnimation;
	float currenTime = 0;
	float desiredTime = .005f;//per frame
	int loops = 7;//how many animations
	Timer timer;
	Spawner* spawner;
	MoveInstance move;






};

