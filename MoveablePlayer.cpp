#include "MoveablePlayer.h"
#include "MathFunctions.h"
#include <iostream>
MoveablePlayer::MoveablePlayer(Tmpl8::vec2* pos, Collider* col, float speed, float DashSpeed) :
	Moveable(pos, col, speed),
	timer(new Timer())


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

bool MoveablePlayer::IsMoving()
{
	return isMoving;
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

	timer->Update(deltaTime);
	Tmpl8::vec2 nextPos = { 0 }, currentPos = *pos;
	hasChangedPos = false;


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
		isMoving = true;
		if (startedDashing)
			startDash();
	}
	else
		isMoving = false;
	if (!startedDashing && timer->isUpdateable == false && dashing) {

		dashing = false;

	}
	if (dashing && timePassed + deltaTime < DASH_DURATION) {

		timePassed += deltaTime;
		float linearT = timePassed / DASH_DURATION;
		nextPos *= MathFunctions::DashFunction(linearT);//this value is from the function graph

	}

	currentPos += nextPos * speed * deltaTime;
	//screen check

	if (Collider::TileMapInGameScreen(currentPos, *col)) {
		(*pos) = currentPos;
		hasChangedPos = true;
	}


}



