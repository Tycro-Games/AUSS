#include "MoveablePlayer.h"
#include <iostream>
MoveablePlayer::MoveablePlayer(Tmpl8::vec2* pos, Collider* col, float speed) :
	Moveable(pos, col, speed),
	timer(new Timer())
	

{
	timer->Init(this, DASH_DURATION);
	Ispeed = speed;
	timer->isUpdateable = false;
}

MoveablePlayer::~MoveablePlayer()
{
	delete timer;
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

void MoveablePlayer::startDash()
{
	if (!timer->isUpdateable) {
		std::cout << "Start!\n";
		timer->isUpdateable = true;
		speed = DASH_SPEED;
	}
}

void MoveablePlayer::Call()
{
	//animation dash to add, use maybe a square + 1
	std::cout << "Stop!\n";
	timer->ResetVar();
	timer->isUpdateable = false;
	speed = Ispeed;
}


void MoveablePlayer::Update(float deltaTime)
{
	timer->Update(deltaTime);
	Tmpl8::vec2 nextPos = { 0 }, currentPos = *pos;
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
	nextPos.normalize();
	currentPos += nextPos * speed * deltaTime;
	//screen check

	if (col->InGameScreen(currentPos, *col)) {
		(*pos) = currentPos;
	}
}



