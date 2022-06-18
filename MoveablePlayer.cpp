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
		nextPos.y -= speed;
	}
	if (down) {
		nextPos.y += speed;
	}
	if (right) {
		nextPos.x += speed;
	}

	if (left) {
		nextPos.x -= speed;
	}
	//add collision check

	currentPos += nextPos;
	//screen check

	if (col->InGameScreen(currentPos, *col)) {
		(*pos) = currentPos;
	}

}



