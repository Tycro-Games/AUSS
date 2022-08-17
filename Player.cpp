#include "Player.h"
#include "MathFunctions.h"


Player::Player(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, Collider* col, int hp)
	:dirToFace(new Tmpl8::vec2()),
	Being(sprite, pos, hp),
	col(col),
	mover(new MoveablePlayer(pos, col)),
	projectileSprite(new Tmpl8::Sprite(new Tmpl8::Surface("assets/missile_big.tga"), 32)),
	explosionSprite(new Tmpl8::Sprite(new Tmpl8::Surface("assets/smoke.tga"), 10)),
	spawner(new Spawner(pos, dirToFace, projectileSprite, explosionSprite))
{

}

Player::~Player()
{
	delete col;
	delete mover;
	delete spawner;
	delete projectileSprite;
	delete explosionSprite;
	pos = nullptr;
}

void Player::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	sprite->Draw(screen, pos->x, pos->y);
	screen->Box(pos->x, pos->y, pos->x + rVar.SPRITE_OFFSET, pos->y + rVar.SPRITE_OFFSET, 0xffffff);
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
void Player::Rotate(float x, float y) {
	//replace with actual pos of player

	dirToFace->x = x - pos->x;
	dirToFace->y = y - pos->y;

	dirToFace->normalize();


	float angle = MathFunctions::GetDirInAnglesPos(*dirToFace);


	angle += rVar.OFFSET_SPRITE;
	angle = fmod(angle, 360);
	frame = angle / rVar.ANGLE_SIZE;

}

MoveablePlayer* Player::GetMoveable()
{
	return mover;
}
Spawner* Player::GetSpawner()
{
	return spawner;
}

