#pragma once
#include "Button.h"
class ExitButton :public Button
{
public:
	ExitButton(Tmpl8::Sprite*, Tmpl8::vec2*, Collider*, Tmpl8::Sprite*, Tmpl8::Sprite*);
	~ExitButton();
	virtual void ChangeSprite() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
};




