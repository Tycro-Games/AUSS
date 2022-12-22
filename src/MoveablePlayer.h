#pragma once


#include "Collider.h"
#include "Timer.h"
#include "MoveToADirection.h"
#include "Curve.h"


class MoveablePlayer final : public Moveable
{
	//json set
	float DASH_SPEED;
	float SPEED;
	float DASH_DURATION;
	float COOLDOWN_DURATION;
	float EDGE_DISTANCE;

public:
	MoveablePlayer();
	void Init(Tmpl8::vec2* _pos, Collider* col, const Collider* _tileMapCol);
	~MoveablePlayer() override = default;

	void Update(float deltaTime) override;
	//setters
	void setUp(bool val = false);
	void setDown(bool val = false);
	void setRight(bool val = false);
	void setLeft(bool val = false);
	void setDash(bool val = false);
	//getters
	float getEdgeBorderDistance() const;
	float getDashLinearTime() const;
	bool getCanRotate() const;
	bool getIsDashing() const;
	bool getTilemapChangedPosition() const;

private:
	//Checks if the vector has at least one component that is zero.
	static bool CheckVecForOneDir(const Tmpl8::vec2& nextPos);
	//Moves and sets the flags for the tilemap and player.
	void MoveTileOrPlayer(const Tmpl8::vec2& tilemapPos, const Collider& c, const Tmpl8::vec2& playerPos) const;

	void InitializeTimers();
	//movement flags
	bool canRotate = false;
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	//tilemap related
	const Collider* tileMapCol;
	bool tilemapMovesOnly = false;
	//dash
	Timer cooldownTimer;
	bool dashing = false;
	Curve dashCurve;

	//timers functions
	void EndCooldown();
};
