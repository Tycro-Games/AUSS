#pragma once
#include "Entity.h"
#include "Timer.h"
class ExplosionBullet :public Entity, public Callable
{
public:
	ExplosionBullet(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos = new Tmpl8::vec2());

	~ExplosionBullet();
	void Init(Tmpl8::vec2 pos);
	virtual void Update(float deltaTime) override;

	virtual void Render(Tmpl8::Surface* screen) override;
	virtual void Call() override;
private:
	Timer* timer;







};

