#pragma once
#include "template.h"

class Moveable
{
public:
	Moveable(Tmpl8::vec2 pos, float speed = 50);
	~Moveable();
	void setUp(bool val = false);
	void setDown(bool val = false);
	void setRight(bool val = false);
	void setLeft(bool val = false);
	void Move();
private:
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	Tmpl8::vec2 pos;

	float speed;
};

