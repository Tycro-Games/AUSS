#pragma once


#include "Collider.h"
#include "Moveable.h"
#include "Timer.h"
class MoveablePlayer :public Moveable, public Callable
{
public:
	MoveablePlayer(Tmpl8::vec2* pos, Collider* col, float speed = 40.0f);
	virtual ~MoveablePlayer();
	virtual void Update(float deltaTime) override;

	void setUp(bool val = false);
	void setDown(bool val = false);
	void setRight(bool val = false);
	void setLeft(bool val = false);
	void setDash(bool val = false);

	void startDash();

	void Dashing();
	bool IsMoving();
private:
	bool isMoving = false;
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	//dash
	Timer* timer;
	bool dashing = false;
	bool startedDashing = false;
	float Ispeed;
	float timePassed = 0.0f;
	const float DASH_DURATION = 0.5f;
	const float DASH_SPEED = 200.0f;

	// Inherited via Callable
	virtual void Call() override;

};

