#pragma once
#include "template.h"

#include "Updateable.h"
#include "Collider.h"

class Moveable :public Updateable
{
public:
	Moveable(Tmpl8::vec2* pos, Collider* col, float speed = 1.0f);
	~Moveable();
	virtual void Update(float deltaTime) override;

	void setUp(bool val = false);
	void setDown(bool val = false);
	void setRight(bool val = false);
	void setLeft(bool val = false);


private:
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	Tmpl8::vec2* pos;
	Collider* col;
	float speed;
};

