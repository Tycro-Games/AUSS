#include "MoveablePlayer.h"
#include "MathFunctions.h"
#include "game.h"

#include <fstream>
#include "nlohmann_json/single_include/nlohmann/json.hpp"
using namespace Tmpl8;


void MoveablePlayer::InitTimers()
{
	//timer Init
	cooldownTimer.Init(std::bind(&MoveablePlayer::EndCooldown, this), COOLDOWN_DURATION);
	cooldownTimer.setUpdateable(false);
}

MoveablePlayer::MoveablePlayer()
	:
	Moveable(),
	tileMapCol(nullptr),
	//lambda expression here, assigns a copy of this function to the dash curve
	dashCurve([](const float x) {return MathFunctions::DashFunction(x); })

{
	//reading speed values
	std::ifstream f("json/PlayerMovement.json");
	json wavesInput = json::parse(f);

	SPEED = wavesInput["speed"];
	DASH_SPEED = wavesInput["dashSpeed"];
	DASH_DURATION = wavesInput["dashDuration"];
	COOLDOWN_DURATION = wavesInput["cooldownDuration"];
	EDGE_DISTANCE = wavesInput["edgeDistance"];

	dashCurve.setScale(DASH_DURATION);
	dashCurve.evaluate(1);//set it at the end

}

void MoveablePlayer::Init(vec2* Pos, Collider* col, const Collider* _tileMapCol)
{
	Moveable::Init(Pos, col, SPEED);
	tileMapCol = _tileMapCol;
	InitTimers();
	dashing = false;
}
void MoveablePlayer::EndCooldown()
{
	cooldownTimer.setUpdateable(false);
}
void MoveablePlayer::Update(const float deltaTime)
{
	cooldownTimer.Update(deltaTime);
	vec2 nextPos = { 0 };
	speed = SPEED;
	if (!dashCurve.isAtEnd()) {
		speed += DASH_SPEED * dashCurve.evaluate(deltaTime);
	}
	if (up) {
		nextPos.y = -speed;
	}
	if (left) {
		nextPos.x = -speed;
	}
	if (down) {
		nextPos.y = speed;
	}
	if (right) {
		nextPos.x = speed;
	}
	nextPos *= deltaTime;

	//collision checking
	const Tilemap& tilemap = Game::Get().getTilemap();


	if (nextPos.x == 0 && nextPos.y == 0) {
		return;
	}
	if (tilemap.IsFreeTile((*pos) + vec2(nextPos.x, 0), *collider)) {

		MoveTileOrPlayer((*tileMapCol->pos) - vec2(nextPos.x, 0), *tileMapCol, (*pos) + vec2(nextPos.x, 0));

	}
	if (tilemap.IsFreeTile((*pos) + vec2(0, nextPos.y), *collider)) {

		MoveTileOrPlayer((*tileMapCol->pos) - vec2(0, nextPos.y), *tileMapCol, (*pos) + vec2(0, nextPos.y));
	}

}

void MoveablePlayer::setDash(const bool val)
{
	if (val && dashCurve.isAtEnd() && !cooldownTimer.getUpdateable()) {
		Game::Get().PlaySound(SoundID::playerDash);
		dashCurve.reset();
		dashing = true;
		cooldownTimer.ResetVar();
		cooldownTimer.setUpdateable(true);
	}
}

float MoveablePlayer::GetEdgeBorderDistance() const
{
	return EDGE_DISTANCE;
}

float MoveablePlayer::GetDashLinearTime() const
{
	return dashCurve.getCurrentValue();
}

bool MoveablePlayer::CanRotate() const
{
	return canRotate;
}

bool MoveablePlayer::IsDashing() const
{
	return !dashCurve.isAtEnd();
}

bool MoveablePlayer::ChangedPos() const
{
	return tilemapMovesOnly;
}

void MoveablePlayer::MoveTileOrPlayer(const vec2& tilemapPos, const Collider& c, const vec2& playerPos) const
{
	//move if it does not hit the bounds
	if (Collider::InGameScreen(tilemapPos, c)) {
		*tileMapCol->pos = tilemapPos;
	}
	else
	{
		Collider playerCollider = (*collider);
		if (Collider::InGameScreen(playerPos, playerCollider * EDGE_DISTANCE)) {

			*pos = playerPos;
		}
	}
}




