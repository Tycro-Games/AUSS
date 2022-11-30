#pragma once


#include "Collider.h"
#include "Timer.h"
#include "MoveToADirection.h"
#include "Rotator.h"
class MoveablePlayer :public Moveable
{
public:
	MoveablePlayer(Tmpl8::vec2* pos, Collider* col, const Collider* tileMapCol, float speed = 70.0f, float dashSpeed = 500);
	MoveablePlayer();
	void Init(Tmpl8::vec2* pos, Collider* col, const Collider* tileMapCol, float speed = 70.0f, float dashSpeed = 500);
	~MoveablePlayer() = default;

	void Update(float deltaTime) override;
	void MovePlayer();

	void setUp(bool val = false)
	{
		up = val;
	}
	void setDown(bool val = false)
	{
		down = val;
	}
	void setRight(bool val = false)
	{
		right = val;
	}
	void setLeft(bool val = false)
	{
		left = val;
	}
	void setDash(bool val = false)
	{
		startedDashing = val;
	}



	float GetDashLinearTime() const
	{
		return linearT;
	}
	bool CanRotate()const
	{
		return canRotate;
	}
	bool IsDashing() const
	{
		return dashTimer.getUpdateable();
	}
	bool ChangedPos() const
	{
		return tilemapMovesOnly;
	}
private:
	void ClampTheMovementVector(const Collider& c, const Tmpl8::vec2 newVec, Tmpl8::vec2& originalVec, const float multiplier = 0.5f);
	bool CheckVecForOneDir(const Tmpl8::vec2& nextPos) const
	{

		return nextPos.x == 0 || nextPos.y == 0;


	}
	void ResetTriggers();
	void SetDashPos(Tmpl8::vec2& nextP);
	void Dash(Tmpl8::vec2& nextPos, float deltaTime);
	void MoveTileOrPlayer(const Tmpl8::vec2& tilemapPos, const Collider& c, const Tmpl8::vec2& playerPos);

	void InitTimers();
	bool tilemapMovesOnly = false;
	bool diagonalMovement = false;
	bool canRotate = false;
	//wasd
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	const Collider* tileMapCol;
	Tmpl8::vec2 playerMovement;

	//dash
	Timer dashTimer;
	Timer cooldownTimer;
	Tmpl8::vec2 nextPos = { 0 };
	Tmpl8::vec2 lastTilemapPos = { 0 };
	Tmpl8::vec2 dashDir;
	bool dashing = false;
	bool startedDashing = false;
	int dashes = 0;
	float initSpeed = 0.0f;
	float dashSpeed;
	float timePassed = 0.0f;
	float linearT = 0.0f;

	//consts
	const float DASH_DURATION = 0.2f;
	const float COOLDOWN_DURATION = 0.1f;
	const float EDGE_DISTANCE = 4.0f;
	//timers functions
	void EndCooldown();
	void EndDash();

};

