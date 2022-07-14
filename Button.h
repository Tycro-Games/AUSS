#pragma once
#include <SDL.h>

#include "surface.h"
#include "Entity.h"
#include "Collider.h"
#include "Timer.h"
class Button :public Entity, public Callable
{
public:
	Button(Tmpl8::Sprite*, Collider*);
	~Button();
	virtual void Update(float deltaTime) override;
	void Fade();
	virtual void Render(Tmpl8::Surface* screen) override;
	virtual void Call() override;
private:
	bool isPressed = false;
	Tmpl8::vec2 offset;
	Tmpl8::Sprite* pressedSprite;
	Collider* cursor;
	Collider* col;
	Timer* timer;

	const float FADE_SPEED = 10;








};

