#pragma once
#include "template.h"

#include "Updateable.h"

class Moveable :public Updateable
{
public:
	Moveable(Tmpl8::vec2* pos, float speed = 50.0f);
	~Moveable();
	void Update(float deltaTime);

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

	float speed;
};

