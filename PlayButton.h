#pragma once
#include "Button.h"
class PlayButton :public Button
{
public:
	PlayButton(Tmpl8::Sprite*, Tmpl8::vec2, Collider*, Tmpl8::Sprite*);
	~PlayButton();

	virtual void ChangeSprite() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
private:
	void ResumeGame();
};




