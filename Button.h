#pragma once
#include <SDL.h>

#include "surface.h"
#include "Entity.h"
class Button :public Entity
{
public:
	Button(Tmpl8::Sprite*);
	~Button();
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
private:
	bool isPressed = false;








};

