#pragma once


#include "Collider.h"
#include "Moveable.h"
#include "Timer.h"
class MoveablePlayer :public Moveable, public Callable
{
public:
	MoveablePlayer(Tmpl8::vec2* pos, Collider* col, Collider* tileMapCol, float speed = 70.0f, float dashSpeed = 500);
	virtual ~MoveablePlayer();
	virtual void Update(float deltaTime) override;
	void MovePlayer();
	void copyInput(MoveablePlayer& p);
	void setUp(bool val = false);
	void setDown(bool val = false);
	void setRight(bool val = false);
	void setLeft(bool val = false);
	void setDash(bool val = false);

	void startDash();

	void Dashing();
	bool CanRotate();
	bool IsDashing() {
		return dashTimer.isUpdateable;
	}
	
	bool ChangedPos() {

		return hasChangedPos;
	};
private:
	bool hasChangedPos = false;
	bool canMove = false;
	bool canRotate = false;
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	Collider* tileMapCol;
	Tmpl8::vec2 playerMovement;

	//dash
	Timer dashTimer;
	Timer cooldownTimer;
	Tmpl8::vec2 dashDir = { 0 };
	bool dashing = false;
	bool startedDashing = false;
	float initSpeed;
	float dashSpeed;
	float timePassed = 0.0f;
	//consts
	const float DASH_DURATION = 0.45f;
	const float COOLDOWN_DURATION = 0.6f;
	const float EDGE_DISTANCE = 5.0f;
	// Inherited via Callable
	virtual void Call() override;

};

