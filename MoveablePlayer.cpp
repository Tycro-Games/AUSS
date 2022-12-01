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
	lastTilemapPos = { 0 };
	dashing = false;
}
void MoveablePlayer::EndCooldown()
{
	cooldownTimer.setUpdateable(false);
}
void MoveablePlayer::Update(float deltaTime)
{
	ResetTriggers();
	cooldownTimer.Update(deltaTime);
	nextPos = { 0 };
	speed = SPEED;
	if (!dashCurve.isAtEnd()) {
		speed += DASH_SPEED * dashCurve.evaluate(deltaTime);
	}
	if (up) {
		nextPos.y = -speed;;
	}
	if (down) {
		nextPos.y = speed;
	}
	if (right) {
		nextPos.x = speed;
	}
	if (left) {
		nextPos.x = -speed;
	}
	nextPos *= deltaTime;

	//collision checking
	const Tilemap& tilemap = Game::Get().getTilemap();

	vec2 yClamped = (*pos) + vec2(0, nextPos.y);
	vec2 xClamped = (*pos) + vec2(nextPos.x, 0);
	if (tilemap.IsFreeTile(yClamped, *collider)) {

		MoveTileOrPlayer((*tileMapCol->pos) - vec2(0, nextPos.y), *tileMapCol, yClamped);

	}
	if (tilemap.IsFreeTile(xClamped, *collider)) {
		MoveTileOrPlayer((*tileMapCol->pos) - vec2(nextPos.x, 0), *tileMapCol, xClamped);

	}

}





//void MoveablePlayer::Dash(vec2& nextPos, float deltaTime)
//{
//	//at least a movement key is pressed
//	if (startedDashing && (nextPos.x != 0 || nextPos.y != 0)) {
//
//		if (!dashTimer.getUpdateable() && !dashing) {
//			dashDir = nextPos;
//			dashes = 0;
//			dashTimer.setUpdateable(true);
//			dashing = true;
//			timePassed = 0;
//
//			//the player will no longer rotate while dashing
//			canRotate = true;
//		}
//
//	}
//	else
//		canRotate = false;
//	if (dashTimer.getUpdateable()) {
//		if (timePassed + deltaTime <= DASH_DURATION) {
//			timePassed += deltaTime;
//			SetDashPos(nextPos);
//		}
//	}
//	dashTimer.Update(deltaTime);
//	if (!startedDashing)
//		cooldownTimer.Update(deltaTime);
//
//}


void MoveablePlayer::MoveTileOrPlayer(const vec2& tilemapPos, const Collider& c, const vec2& playerPos)
{
	//move if it does not hit the bounds
	if (Collider::InGameScreen(tilemapPos, c)) {
		*tileMapCol->pos = tilemapPos;
	}
	else
	{
		std::cout << "move player at:";
		MovePlayer(playerPos);
	}


}

void MoveablePlayer::ResetTriggers()
{
	tilemapMovesOnly = false;
	diagonalMovement = false;

}

void MoveablePlayer::MovePlayer(const Tmpl8::vec2& playerMovement)
{
	Collider c = (*collider);
	if (Collider::InGameScreen(playerMovement, c * EDGE_DISTANCE)) {
		*pos = playerMovement;
	}

	////tilemap cannot move anymore so only the player moves
	//float spe = 1.0f;
	//if (diagonalMovement) {

	//	//if the tile has also moved half the speed
	//	spe = 0.5f;
	//}

	//ClampTheMovementVector(c, playerMovement, *pos, spe);
	//if (diagonalMovement)//movement on the edges of the map
	//{
	//	//move the tilemap again
	//	ClampTheMovementVector(*tileMapCol, lastTilemapPos + *tileMapCol->pos, *tileMapCol->pos);
	//	if (!diagonalMovement)//player shoud move again
	//		ClampTheMovementVector(c, playerMovement, *pos, spe);


	//}

}


void MoveablePlayer::ClampTheMovementVector(const Collider& c, const vec2 newVec, vec2& originalVec, const float multiplier)
{
	//try to move the player only on one axis
	vec2 nextPos = newVec - originalVec;

	if (CheckVecForOneDir(nextPos))
		return;
	vec2 orginalPos = originalVec;
	vec2 clampedOnX = vec2(originalVec.x + nextPos.x * multiplier, originalVec.y);
	vec2 clampedOnY = vec2(originalVec.x, originalVec.y + nextPos.y * multiplier);
	if (Collider::InGameScreen(clampedOnX, c))
		originalVec = clampedOnX, diagonalMovement = true;
	else if (Collider::InGameScreen(clampedOnY, c))
		originalVec = clampedOnY, diagonalMovement = true;

}
