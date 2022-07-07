#include "MoveablePlayer.h"
MoveablePlayer::MoveablePlayer(Tmpl8::vec2* pos, Collider* col, float speed) :
	Moveable(pos, col, speed)

{}

MoveablePlayer::~MoveablePlayer()
{
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


void MoveablePlayer::Update(float deltaTime)
{

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



