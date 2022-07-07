#pragma once


#include "Collider.h"
#include "Moveable.h"
class MoveablePlayer :public Moveable
{
public:
	MoveablePlayer(Tmpl8::vec2* pos, Collider* col, float speed = 20.0f);
	virtual ~MoveablePlayer();
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

};

