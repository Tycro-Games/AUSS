#include "Player.h"
#include "MathFunctions.h"


Player::Player(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, Collider* col, int hp)
	:dirToFace(new Tmpl8::vec2()),
	Being(sprite, pos, hp),
	col(col),
	mover(new Moveable(pos, col)),
	spawner(new Spawner(new Tmpl8::Sprite(new Tmpl8::Surface("assets/missile_big.tga"), 16),
		pos,
		dirToFace,
		0.5f))
{

}

Player::~Player()
{
	delete col;
	delete mover;
	delete spawner;
	pos = nullptr;
}

void Player::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	sprite->Draw(screen, pos->x, pos->y);
	screen->Box(pos->x, pos->y, pos->x + SPRITE_OFFSET, pos->y + SPRITE_OFFSET, 0xffffff);
	spawner->Render(screen);
}

void Player::Update(float deltaTime)
{
	mover->Update(deltaTime);
	spawner->Update(deltaTime);

}
void Player::Shoot(bool fire)
{
	spawner->setFlag(fire);
}
void Player::Rotate(int x, int y) {
	//replace with actual pos of player
	dirToFace->x = x - pos->x;
	dirToFace->y = y - pos->y;

	dirToFace->normalize();


	float angle = MathFunctions::GetDirInAngles(*dirToFace);


	angle += OFFSET_SPRITE;
	angle = fmod(angle, 360);
	frame = angle / ANGLE_SIZE;
}

Moveable* Player::GetMoveable()
{
	return mover;
}


