#include "Player.h"
#include "MathFunctions.h"
#include <string>
#include"game.h"

Player::Player(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, Collider* col, int hp)
	:dirToFace(new Tmpl8::vec2()),
	Being(sprite, pos, hp),
	col(col),
	mover(new MoveablePlayer(pos, col)),
	projectileSprite(new Tmpl8::Sprite(new Tmpl8::Surface("assets/missile_big.tga"), 32)),
	explosionSprite(new Tmpl8::Sprite(new Tmpl8::Surface("assets/smoke.tga"), 10)),
	spawner(new ProjectileSpawner(pos, dirToFace, projectileSprite, explosionSprite))
{
	timer = (new Timer(this, TIME_TO_HIT));
}

Player::~Player()
{
	delete timer;
	delete col;
	delete mover;
	delete spawner;

	delete dirToFace;
	delete projectileSprite;

}

void Player::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	sprite->Draw(screen, pos->x, pos->y);
	screen->Box(pos->x, pos->y, pos->x + rVar.SPRITE_OFFSET, pos->y + rVar.SPRITE_OFFSET, 0xffffff);
	spawner->Render(screen);
	auto inactive = std::string("HP: " + std::to_string(hp));

	screen->Print(inactive.c_str(), 10, 40, 0xffffffff);
}

void Player::Update(float deltaTime)
{
	mover->Update(deltaTime);
	spawner->Update(deltaTime);
	timer->Update(deltaTime);
}
void Player::TakeDamage(int dg) {
	if (timer->isFinished) {
		Being::TakeDamage(dg);
		timer->ResetVar();
	}

}
void Player::Shoot(bool fire)
{
	spawner->setFlag(fire);
}
void Player::Rotate(float x, float y) {
	//replace with actual pos of player

	MathFunctions::RotateTo(x, y, *pos, dirToFace);


	float angle = MathFunctions::GetDirInAnglesPos(*dirToFace);


	angle += rVar.OFFSET_SPRITE;
	angle = fmod(angle, 360);
	frame = angle / rVar.ANGLE_SIZE;

}

MoveablePlayer* Player::GetMoveable()
{
	return mover;
}
ProjectileSpawner* Player::GetSpawner()
{
	return spawner;
}

void Player::Die()
{
	std::cout << "RESET GAME";
	
	Tmpl8::Game::ChangeGameState(Tmpl8::Game::GameState::reset);
}

