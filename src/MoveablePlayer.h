#pragma once


#include "Collider.h"
#include "Timer.h"
#include "MoveToADirection.h"
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
	void Init(Tmpl8::vec2* Pos, Collider* col, const Collider* _tileMapCol);
	~MoveablePlayer() override = default;

	void Update(float deltaTime) override;

	void setUp(const bool val = false)
	{
		up = val;
	}
	void setDown(const bool val = false)
	{
		down = val;
	}
	void setRight(const bool val = false)
	{
		right = val;
	}
	void setLeft(const bool val = false)
	{
		left = val;
	}
	void setDash(bool val = false);

	float GetEdgeBorderDistance() const;
	float GetDashLinearTime() const;

	bool CanRotate() const;

	bool IsDashing() const;

	bool ChangedPos() const;

private:
	static bool CheckVecForOneDir(const Tmpl8::vec2& nextPos)
	{
		return nextPos.x == 0 || nextPos.y == 0;
	}
	void MoveTileOrPlayer(const Tmpl8::vec2& tilemapPos, const Collider& c, const Tmpl8::vec2& playerPos) const;

	void InitTimers();
	bool tilemapMovesOnly = false;
	bool canRotate = false;
	//use for w a s d
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	const Collider* tileMapCol;
	//dash
	Timer cooldownTimer;
	bool dashing = false;

	//timers functions
	void EndCooldown();

	Curve dashCurve;
};

