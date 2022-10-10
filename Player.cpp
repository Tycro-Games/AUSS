#include "Player.h"
#include "MathFunctions.h"
#include <string>
#include"game.h"

Player::Player(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, Collider* col, MoveablePlayer* movements, int hp)
	:dirToFace(new Tmpl8::vec2()),
	Being(sprite, pos, hp),
	startingPos(pos),
	col(col),
	map(map),
	otherMovements(movements),
	projectileSprite(new Tmpl8::Sprite(new Tmpl8::Surface("assets/missile_big.tga"), 32))

{
	spawner = new ProjectileSpawner(&this->pos, -Tmpl8::vec2(rVar.SPRITE_OFFSET / 2, rVar.SPRITE_OFFSET / 2),
		dirToFace,
		projectileSprite,
		new Tmpl8::Sprite(new Tmpl8::Surface("assets/smoke.tga"), 10));
	colMover = (*col) * EDGE_DISTANCE;
	playerMover = new MoveablePlayer(&this->pos, &colMover);
	timer = (new Timer(this, TIME_TO_HIT));
}

Player::~Player()
{
	delete timer;
	delete col;
	delete playerMover;
	delete spawner;
	delete dirToFace;
	delete projectileSprite;

}

void Player::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2), static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2));
	//debug for player's collider	
	screen->Box(static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2), static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2), static_cast<int>(pos.x + rVar.SPRITE_OFFSET / 2), static_cast<int>(pos.y + rVar.SPRITE_OFFSET / 2), 0xffffff);
	//debug for collision with screen borders
	screen->Box(static_cast<int>(pos.x + colMover.min.x), static_cast<int>(pos.y + colMover.min.y), static_cast<int>(pos.x + colMover.max.x), static_cast<int>(pos.y + colMover.max.y), 0xffffff);

	spawner->Render(screen);
	auto inactive = std::string("HP: " + std::to_string(hp));

	screen->Print(inactive.c_str(), 10, 40, 0x00000000);
}

void Player::Update(float deltaTime)
{
	//copy the input from the player to the tilemap mover
	playerMover->copyInput(*otherMovements);
	otherMovements->Update(deltaTime);

	if (!otherMovements->ChangedPos()) {
		//tilemap is trying to go past the limits
		//move player instead
		playerMover->Update(deltaTime);

	}

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
void Player::Rotate(int x, int y) {
	//replace with actual pos of player

	MathFunctions::RotateTo(static_cast<float>(x), static_cast<float>(y), pos, dirToFace);


	float angle = MathFunctions::GetDirInAnglesPos(*dirToFace);


	angle += rVar.OFFSET_SPRITE;
	angle = static_cast<float>(fmod(angle, 360));
	frame = static_cast<int>(angle / rVar.ANGLE_SIZE);

}

MoveablePlayer* Player::GetMoveable()
{
	return playerMover;
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

