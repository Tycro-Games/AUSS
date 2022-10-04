#pragma once


#include "Collider.h"
#include "Moveable.h"
#include "Timer.h"
class MoveablePlayer :public Moveable, public Callable
{
public:
	MoveablePlayer(Tmpl8::vec2* pos, Collider* col, float speed = 40.0f, float dashSpeed = 200);
	virtual ~MoveablePlayer();
	virtual void Update(float deltaTime) override;
	void copyInput(MoveablePlayer& p);
	void setUp(bool val = false);
	void setDown(bool val = false);
	void setRight(bool val = false);
	void setLeft(bool val = false);
	void setDash(bool val = false);

	void startDash();

	void Dashing();
	bool IsMoving();
	bool ChangedPos() {
		return hasChangedPos;
	};
private:
	bool hasChangedPos = false;
	bool isMoving = false;
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	//dash
	Timer* timer;
	bool dashing = false;
	bool startedDashing = false;
	float initSpeed;
	float dashSpeed;
	float timePassed = 0.0f;
	const float DASH_DURATION = 0.5f;

	// Inherited via Callable
	virtual void Call() override;

};

