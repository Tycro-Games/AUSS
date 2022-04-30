#include "Player.h"
#include "MathFunctions.h"


Player::Player(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, int hp)
	:Being(sprite, pos, hp),
	mover(new Moveable(pos))
{

}

Player::~Player()
{
	delete mover;
}

void Player::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	sprite->Draw(screen, pos->x, pos->y);
}

void Player::Update(float deltaTime)
{
	mover->Update(deltaTime);
}
void Player::Rotate(int x, int y) {
	//replace with actual pos of player
	dirToFace.x = x - pos->x;
	dirToFace.y = y - pos->y;

	dirToFace.normalize();


	float angle = MathFunctions::GetDirInAngles(dirToFace);


	angle += OFFSET_SPRITE;
	angle = fmod(angle, 360);
	frame = angle / ANGLE_SIZE;
}


