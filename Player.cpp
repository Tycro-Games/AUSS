#include "Player.h"
#include "MathFunctions.h"


Player::Player(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, Collider* col, int hp)
	:Being(sprite, pos, hp),
	col(col),
	mover(new Moveable(pos, col))
{}

Player::~Player()
{
	delete col;
	delete mover;
}

void Player::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	sprite->Draw(screen, pos->x, pos->y);
	screen->Box(pos->x, pos->y, pos->x + SPRITE_OFFSET, pos->y + SPRITE_OFFSET, 0xffffff);
}

void Player::Update(float deltaTime)
{
	mover->Update(deltaTime);

}
void Player::Shoot(bool fire)
{

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

Moveable* Player::GetMoveable()
{
	return mover;
}


