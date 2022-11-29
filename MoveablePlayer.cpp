#include "MoveablePlayer.h"
#include "MathFunctions.h"
#include "game.h"

#include <iostream>
using namespace Tmpl8;
MoveablePlayer::MoveablePlayer(vec2* pos, Collider* playerCollider, const Collider* tileMapCol, float speed, float _dashSpeed) :
	Moveable(pos, playerCollider, speed),
	tileMapCol(tileMapCol)

{
	initSpeed = speed;
	dashSpeed = _dashSpeed;
	InitTimers();
}

void MoveablePlayer::InitTimers()
{
	//timer Init
	cooldownTimer.Init(std::bind(&MoveablePlayer::EndCooldown, this), COOLDOWN_DURATION);
	cooldownTimer.setUpdateable(false);
	dashTimer.Init(std::bind(&MoveablePlayer::EndDash, this), DASH_DURATION);
	dashTimer.setUpdateable(false);
}

MoveablePlayer::MoveablePlayer()
	:
	Moveable(),
	tileMapCol(nullptr)
{
	dashSpeed = 0;
}

void MoveablePlayer::Init(vec2* pos, Collider* col, const Collider* _tileMapCol, float speed, float _dashSpeed)
{
	Moveable::Init(pos, col, speed);
	tileMapCol = _tileMapCol;
	dashSpeed = _dashSpeed;
	initSpeed = speed;

	InitTimers();
}
void MoveablePlayer::EndCooldown()
{

	cooldownTimer.ResetVar();
	cooldownTimer.setUpdateable(false);
	dashing = false;

}
bool MoveablePlayer::CheckPositionForCollisions(const Tmpl8::vec2& playerPos, const Collider& playerCollider) const {
	const Tilemap& tilemap = Game::Get().getTilemap();
	return tilemap.IsFree(playerPos.x + playerCollider.min.x, playerPos.y + playerCollider.min.y) &&
		tilemap.IsFree(playerPos.x + playerCollider.max.x, playerPos.y + playerCollider.min.y) &&
		tilemap.IsFree(playerPos.x + playerCollider.min.x, playerPos.y + playerCollider.max.y) &&
		tilemap.IsFree(playerPos.x + playerCollider.max.x, playerPos.y + playerCollider.max.y);
}
void MoveablePlayer::EndDash()
{
	dashTimer.ResetVar();
	dashTimer.setUpdateable(false);
	speed = initSpeed;
	//start the cooldown
	cooldownTimer.setUpdateable(true);
}


void MoveablePlayer::Update(float deltaTime)
{
	ResetTriggers();

	cooldownTimer.Update(deltaTime);
	dashTimer.Update(deltaTime);


	nextPos = { 0 };


	if (up) {
		nextPos.y--;
	}
	if (down) {
		nextPos.y++;
	}
	if (right) {
		nextPos.x++;
	}
	if (left) {
		nextPos.x--;
	}
	//if the player goes on a diagonal the vector will not have a maginitude of 1
	if (nextPos.length() > 0)
		nextPos.normalize();

	//dashing
	StartDashing(nextPos, deltaTime);

	//collision checking

	//tile check
	vec2 playerPos = *pos;
	const Collider playerCol = *collider;
	playerPos += nextPos * speed * deltaTime;


	const float playerPosOnX = nextPos.x * speed * deltaTime;
	const float  playerPosOnY = nextPos.y * speed * deltaTime;


	vec2 tilemapPos = *tileMapCol->pos;
	const Collider c = *tileMapCol;
	tilemapPos += nextPos * (-speed) * deltaTime;


	if (CheckPositionForCollisions(playerPos, playerCol)) {
		MoveTileOrPlayer(tilemapPos, c, playerPos);
	}
	else {
		//moving diagonally and hitting an obstacle
		if (nextPos.x != 0 && nextPos.y != 0) {
			if (CheckPositionForCollisions((*pos) + vec2(0, playerPosOnY), playerCol)) {
				MoveTileOrPlayer((*c.pos) - vec2(0, playerPosOnY), c, (*pos) + vec2(0, playerPosOnY));
			}
			else if (CheckPositionForCollisions((*pos) + vec2(playerPosOnX, 0), playerCol)) {
				MoveTileOrPlayer((*c.pos) - vec2(playerPosOnX, 0), c, (*pos) + vec2(playerPosOnX, 0));
			}
		}
	}

}

void MoveablePlayer::StartDashing(vec2& nextPos, float deltaTime)
{
	//at least a movement key is pressed
	if (nextPos.x != 0 || nextPos.y != 0) {
		//the player will no longer rotate while dashing
		canRotate = true;
		if (startedDashing) {
			dir = nextPos;
			if (!dashTimer.getUpdateable() && !dashing) {
				dashes = 0;
				dashTimer.setUpdateable(true);
				dashing = true;
				timePassed = 0;
				speed = dashSpeed;
			}
		}
	}
	else
		canRotate = false;

	if (dashTimer.getUpdateable() == false && dashing && !startedDashing) {
		//start the cooldown then the dash is finished
		cooldownTimer.setUpdateable(true);
	}
	if (dashing && timePassed + deltaTime < DASH_DURATION) {
		timePassed += deltaTime;
		SetDashPos(nextPos);//this value is from the function graph
	}

}


void MoveablePlayer::MoveTileOrPlayer(const vec2& tilemapPos, const Collider& c, const vec2& playerPos)
{
	diagonalMovement = false;
	//move getTilemap() if it does not hit the bounds
	if (Collider::InGameScreen(tilemapPos, c)) {
		*tileMapCol->pos = tilemapPos;
		hasChangedPos = true;

	}
	else
	{
		//this could also move the player so we need to limit the speed
		lastTilemapPos = tilemapPos - (*tileMapCol->pos);
		ClampTheMovementVector(c, tilemapPos, *tileMapCol->pos);
		//player can move
		canMove = true;
		playerMovement = playerPos;

	}

}
void MoveablePlayer::SetDashPos(vec2& nextPos)
{
	linearT = timePassed / DASH_DURATION;
	nextPos = dir;
	nextPos *= MathFunctions::DashFunction(linearT);
}

void MoveablePlayer::ResetTriggers()
{

	canMove = false;
	hasChangedPos = false;
}

void MoveablePlayer::MovePlayer()
{
	if (canMove) {
		Collider c = (*collider);
		if (Collider::InGameScreen(playerMovement, c * EDGE_DISTANCE))
			*pos = playerMovement;
		else {
			//tile cannot move anymore so only the player moves
			float spe = 1.0f;
			//if the tile has also moved half the speed
			if (diagonalMovement)
				spe = 0.5f;

			ClampTheMovementVector(c, playerMovement, *pos, spe);
			if (diagonalMovement)
			{
				//move the tilemap again
				ClampTheMovementVector(*tileMapCol, lastTilemapPos + *tileMapCol->pos, *tileMapCol->pos);
				if (!diagonalMovement)//player shoud move again
					ClampTheMovementVector(c, playerMovement, *pos, spe);


			}
			diagonalMovement = false;
		}
	}
}

void MoveablePlayer::ClampTheMovementVector(const Collider& c, const vec2 newVec, vec2& originalVec, const float multiplier)
{
	//try to move the player only on one axis
	vec2 nextPos = newVec - originalVec;
	if (CheckVecForOneDir(nextPos))
		return;

	vec2 clampedOnX = vec2(originalVec.x + nextPos.x * multiplier, originalVec.y);
	vec2 clampedOnY = vec2(originalVec.x, originalVec.y + nextPos.y * multiplier);
	if (Collider::InGameScreen(clampedOnX, c))
		originalVec = clampedOnX, diagonalMovement = true;
	else if (Collider::InGameScreen(clampedOnY, c))
		originalVec = clampedOnY, diagonalMovement = true;
}
