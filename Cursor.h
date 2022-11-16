#pragma once
#include "Entity.h"
#include "Collider.h"
class Cursor :public Entity
{
public:
	Cursor(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos = Tmpl8::vec2(0));
	void AddOffset();
	~Cursor();
	virtual void Update(float deltaTime) override;
	void ChangePosition(int x, int y);
	virtual void Render(Tmpl8::Surface* screen) override;
	Collider& GetCollider() {
		return col;
	}
private:
	const Tmpl8::vec2 offset = { -13,-13 };
	Collider col;



};

