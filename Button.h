#pragma once


#include "Entity.h"
#include "Collider.h"
#include "Timer.h"
class Button :public Entity
{
public:
	Button(Tmpl8::Sprite*, Tmpl8::vec2, Collider&, Tmpl8::Sprite*);
	virtual ~Button();
	virtual void ChangeSprite() = 0;
	virtual void Update(float deltaTime) override;
	void Init();

	virtual void Render(Tmpl8::Surface* screen) override;

protected:
	void CheckHovering();
	bool isPressed = false;
	Tmpl8::vec2 offset;
	Tmpl8::Sprite* pressedSprite;
	Collider* cursor;
	Collider* col;
	bool isHovering = false;
};

