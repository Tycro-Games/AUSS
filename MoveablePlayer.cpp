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

void MoveablePlayer::Init(vec2* pos, Collider* col, const Collider* _tileMapCol, float _speed, float _dashSpeed)
{
	Moveable::Init(pos, col, _speed);
	tileMapCol = _tileMapCol;
	dashSpeed = _dashSpeed;
	initSpeed = _speed;
	speed = _speed;
	InitTimers();
	lastTilemapPos = { 0 };
	dashing = false;
}
void MoveablePlayer::EndCooldown()
{

	cooldownTimer.ResetVar();
	cooldownTimer.setUpdateable(false);
	dashing = false;

}

void MoveablePlayer::EndDash()
{
	dashTimer.ResetVar();
	dashTimer.setUpdateable(false);
	cooldownTimer.setUpdateable(true);
	speed = initSpeed;
}


void MoveablePlayer::Update(float deltaTime)
{
	ResetTriggers();




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

	Dash(nextPos, deltaTime);

	//collision checking

	//tile check
	vec2 playerPos = *pos;
	playerPos += nextPos * speed * deltaTime;


	const float playerPosOnX = nextPos.x * speed * deltaTime;
	const float  playerPosOnY = nextPos.y * speed * deltaTime;

	//tile movement
	vec2 tilemapPos = *tileMapCol->pos;
	tilemapPos += nextPos * (-speed) * deltaTime;

	const Tilemap& tilemap = Game::Get().getTilemap();

	if (tilemap.IsFreeTile(playerPos, *collider)) {
		MoveTileOrPlayer(tilemapPos, *tileMapCol, playerPos);
	}
	else if (nextPos.x != 0 && nextPos.y != 0) {
		//moving diagonally and hitting an obstacle
		if (tilemap.IsFreeTile((*pos) + vec2(0, playerPosOnY), *collider)) {
			MoveTileOrPlayer((*tileMapCol->pos) - vec2(0, playerPosOnY), *tileMapCol, (*pos) + vec2(0, playerPosOnY));
			if (dashTimer.getUpdateable()) {
				//change dash direction
				dashDir = vec2{ 0,playerPosOnY }.normalized();
			}
		}
		else if (tilemap.IsFreeTile((*pos) + vec2(playerPosOnX, 0), *collider)) {
			MoveTileOrPlayer((*tileMapCol->pos) - vec2(playerPosOnX, 0), *tileMapCol, (*pos) + vec2(playerPosOnX, 0));
			if (dashTimer.getUpdateable()) {
				//change dash direction
				dashDir = vec2{ playerPosOnX,0 }.normalized();
			}

		}
	}
}


void MoveablePlayer::Dash(vec2& nextPos, float deltaTime)
{
	//at least a movement key is pressed
	if (startedDashing && (nextPos.x != 0 || nextPos.y != 0)) {

		if (!dashTimer.getUpdateable() && !dashing) {
			dashDir = nextPos;
			dashes = 0;
			dashTimer.setUpdateable(true);
			dashing = true;
			timePassed = 0;

			//the player will no longer rotate while dashing
			canRotate = true;
		}

	}
	else
		canRotate = false;
	if (dashTimer.getUpdateable()) {
		if (timePassed + deltaTime <= DASH_DURATION) {
			timePassed += deltaTime;
			SetDashPos(nextPos);
		}
	}
	dashTimer.Update(deltaTime);
	if (!startedDashing)
		cooldownTimer.Update(deltaTime);

}


void MoveablePlayer::MoveTileOrPlayer(const vec2& tilemapPos, const Collider& c, const vec2& playerPos)
{
	diagonalMovement = false;
	//move if it does not hit the bounds
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
	nextPos = dashDir;
	speed = dashSpeed * MathFunctions::DashFunction(linearT);
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
			//tilemap cannot move anymore so only the player moves
			float spe = 1.0f;
			if (diagonalMovement) {

				//if the tile has also moved half the speed
				spe = 0.5f;
			}

			ClampTheMovementVector(c, playerMovement, *pos, spe);
			if (diagonalMovement)//movement on the edges of the map
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
	vec2 orginalPos = originalVec;
	vec2 clampedOnX = vec2(originalVec.x + nextPos.x * multiplier, originalVec.y);
	vec2 clampedOnY = vec2(originalVec.x, originalVec.y + nextPos.y * multiplier);
	if (Collider::InGameScreen(clampedOnX, c))
		originalVec = clampedOnX, diagonalMovement = true;
	else if (Collider::InGameScreen(clampedOnY, c))
		originalVec = clampedOnY, diagonalMovement = true;

}
