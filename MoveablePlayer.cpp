#include "MoveablePlayer.h"
#include "MathFunctions.h"
#include "game.h"

#include <iostream>
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
	dashCurve([](float x) {return MathFunctions::DashFunction(x); }, DASH_DURATION)
{
	dashCurve.evaluate(1);//set it at the end
}

void MoveablePlayer::Init(vec2* pos, Collider* col, const Collider* _tileMapCol, float _speed, float _dashSpeed)
{
	Moveable::Init(pos, col, _speed);
	tileMapCol = _tileMapCol;
	speed = _speed;
	InitTimers();
	dashing = false;
}
void MoveablePlayer::EndCooldown()
{
	cooldownTimer.setUpdateable(false);
}
void MoveablePlayer::Update(float deltaTime)
{
	cooldownTimer.Update(deltaTime);
	vec2 nextPos = { 0 };
	speed = SPEED;
	if (!dashCurve.isAtEnd()) {
		speed += DASH_SPEED * dashCurve.evaluate(deltaTime);
	}
	if (up) {
		nextPos.y = -speed;;
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


	if (nextPos.x == 0 && nextPos.y == 0)
		return;
	if (tilemap.IsFreeTile((*pos) + vec2(nextPos.x, 0), *collider)) {

		MoveTileOrPlayer((*tileMapCol->pos) - vec2(nextPos.x, 0), *tileMapCol, (*pos) + vec2(nextPos.x, 0));

	}
	if (tilemap.IsFreeTile((*pos) + vec2(0, nextPos.y), *collider)) {

		MoveTileOrPlayer((*tileMapCol->pos) - vec2(0, nextPos.y), *tileMapCol, (*pos) + vec2(0, nextPos.y));
	}
}

void MoveablePlayer::MoveTileOrPlayer(const vec2& tilemapPos, const Collider& c, const vec2& playerPos)
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




