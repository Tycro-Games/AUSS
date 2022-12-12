#pragma once


#include "Collider.h"
#include "Timer.h"
#include "MoveToADirection.h"
#include "Rotator.h"
#include "Curve.h"


class MoveablePlayer :public Moveable
{
	//consts

	//json set
	float DASH_SPEED;
	float SPEED;
	float DASH_DURATION;
	float COOLDOWN_DURATION;
	float EDGE_DISTANCE;
public:
	MoveablePlayer();
	void Init(Tmpl8::vec2* pos, Collider* col, const Collider* tileMapCol);
	~MoveablePlayer() = default;

	void Update(float deltaTime) override;

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
		if (val && dashCurve.isAtEnd() && !cooldownTimer.getUpdateable()) {
			dashCurve.reset();
			dashing = true;
			cooldownTimer.ResetVar();
			cooldownTimer.setUpdateable(true);
		}
	}
	float GetEdgeBorderDistance() const {
		return EDGE_DISTANCE;
	}
	float GetDashLinearTime() const
	{
		return dashCurve.getCurrentValue();
	}
	bool CanRotate()const
	{
		return canRotate;
	}
	bool IsDashing() const
	{
		return !dashCurve.isAtEnd();
	}
	bool ChangedPos() const
	{
		return tilemapMovesOnly;
	}
private:
	bool CheckVecForOneDir(const Tmpl8::vec2& nextPos) const
	{
		return nextPos.x == 0 || nextPos.y == 0;
	}
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
	//dash
	Timer cooldownTimer;
	bool dashing = false;
	int dashes = 0;


	//timers functions
	void EndCooldown();

	Curve dashCurve;
};

