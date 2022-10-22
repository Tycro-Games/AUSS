#include "MoveablePlayer.h"
#include "MathFunctions.h"
#include <iostream>
#include "game.h"
MoveablePlayer::MoveablePlayer(Tmpl8::vec2* pos, Collider* col, Collider* tileMapCol, Player* player, float speed, float DashSpeed) :
	Moveable(pos, col, speed),
	timer(new Timer()),
	tileMapCol(tileMapCol),
	player(player)


{

	timer->Init(this, DASH_DURATION);
	initSpeed = speed;
	dashSpeed = DashSpeed;
	timer->isUpdateable = false;
}

MoveablePlayer::~MoveablePlayer()
{
	delete timer;
}
void MoveablePlayer::copyInput(MoveablePlayer& p) {
	p.setDash(startedDashing);
	p.setDown(down);
	p.setLeft(left);
	p.setRight(right);
	p.setUp(up);
}
void MoveablePlayer::setUp(bool val)
{
	up = val;
}

void MoveablePlayer::setDown(bool val)
{
	down = val;
}

void MoveablePlayer::setRight(bool val)
{
	right = val;
}

void MoveablePlayer::setLeft(bool val)
{
	left = val;
}

void MoveablePlayer::setDash(bool val)
{
	startedDashing = val;
}



void MoveablePlayer::startDash()
{
	if (!timer->isUpdateable && !dashing) {


		timer->isUpdateable = true;

		Dashing();
	}
}

void MoveablePlayer::Dashing()
{
	dashing = true;
	timePassed = 0;
	speed = dashSpeed;
}

bool MoveablePlayer::CanRotate()
{
	return canRotate;
}

void MoveablePlayer::Call()
{

	//animation dash to add, use maybe a square + 1
	timer->ResetVar();
	timer->isUpdateable = false;
	speed = initSpeed;


}


void MoveablePlayer::Update(float deltaTime)
{

	hasChangedPos = false;
	timer->Update(deltaTime);

	Tmpl8::vec2 nextPos = { 0 };

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
	//add collision check
	if (nextPos.length() > 0)
		nextPos.normalize();
	//dashing
	if ((nextPos.x != 0 || nextPos.y != 0)) {
		canRotate = true;
		if (startedDashing)
			startDash();
	}
	else
		canRotate = false;

	if (!startedDashing && timer->isUpdateable == false && dashing) {
		dashing = false;

	}
	if (dashing && timePassed + deltaTime < DASH_DURATION) {

		timePassed += deltaTime;
		float linearT = timePassed / DASH_DURATION;
		nextPos *= MathFunctions::DashFunction(linearT);//this value is from the function graph

	}
	//player or tilemap
	Tmpl8::vec2 currentPos = *pos;
	Collider c = *col;
	//tile check
	Tmpl8::vec2 tilePos = *pos;
	Collider tileCol = *col;

	float spe = speed;
	//the tile check position
	tilePos += nextPos * spe * deltaTime;


	//checks if the player or the tilemap should be moved
	if (!movingPlayer) {
		currentPos = *tileMapCol->pos;
		c = *tileMapCol;
		spe = -spe;

	}

	currentPos += nextPos * spe * deltaTime;
	Collider obs;
	//checks collision with obstacles
	if (Tmpl8::Game::tileMap->IsFree(tilePos.x + tileCol.min.x, tilePos.y + tileCol.min.y, obs) &&
		Tmpl8::Game::tileMap->IsFree(tilePos.x + tileCol.max.x, (tilePos.y + tileCol.min.y), obs) &&
		Tmpl8::Game::tileMap->IsFree(tilePos.x + tileCol.min.x, (tilePos.y + tileCol.max.y), obs) &&
		Tmpl8::Game::tileMap->IsFree(tilePos.x + tileCol.max.x, (tilePos.y + tileCol.max.y), obs)) {
		//tilemap checks
		if (!movingPlayer) {
			if (Collider::TileMapInGameScreen(currentPos, c)) {

				*tileMapCol->pos = currentPos;
				hasChangedPos = true;
			}
		}//player checks
		else if (Collider::TileMapInGameScreen(currentPos, c * EDGE_DISTANCE))
		{
			*pos = currentPos;
		}
	}
	else if (dashing) {
		std::cout << "bounce\n";
		Tmpl8::vec2 reflected = MathFunctions::Reflect(nextPos, Collider::GetNormal(obs, *col));
		player->Rotate(reflected.x, reflected.y);
	}


	movingPlayer = false;


}



