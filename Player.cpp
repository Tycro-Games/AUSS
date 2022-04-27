#include "Player.h"
#include "MathFunctions.h"


Player::Player(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, int hp)
	:Being(sprite, pos, hp)
{}

Player::~Player()
{
}

void Player::Update(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	sprite->Draw(screen, 100, 200);

}
void Player::Rotate(int x, int y) {
	//replace with actual pos of player
	dir.x = x - 100;
	dir.y = y - 200;

	dir.normalize();


	float angle = MathFunctions::GetDirInAngles(dir);


	angle += 90;//offset for the image
	angle = fmod(angle, 360);
	frame = angle / angleSize;
}
