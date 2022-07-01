#pragma once
#include "Entity.h"
class FollowCursor :public Entity
{
public:
	FollowCursor(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos = new Tmpl8::vec2());
	~FollowCursor();
	virtual void Update(float deltaTime) override;
	void ChangePosition(int x, int y);
	virtual void Render(Tmpl8::Surface* screen) override;
private:
	const Tmpl8::vec2 offset = { -13,-13 };




};

