#include "Player.h"
#include "MathFunctions.h"
#include "game.h"
#include "Rotator.h"

#include <string>
using namespace Tmpl8;
Player::Player() :
	spawner(-Tmpl8::vec2(rVar.SPRITE_OFFSET / 2, rVar.SPRITE_OFFSET / 2),
		spriteProjectilePath,
		spriteExplosionPath),
	tilemapCollider(nullptr),
	playerMover(nullptr)
{

}

void Player::Init(const Collider& tileMapCollider, const Tmpl8::vec2& _pos)
{

	Being::Init(spritePlayerPath, 32, _pos, 100);
	startingPos = _pos;
	playerCollider = Collider(COL_MIN, COL_MAX, &startingPos);

	tilemapCollider = &tileMapCollider;

	lastPos = _pos;

	timer.init(this, TIME_TO_HIT);
	spawner.Init();
	playerMover = new MoveablePlayer(&pos, &playerCollider, tilemapCollider);
}

Player::~Player()
{
	delete playerMover;

}


void Player::Render(Tmpl8::Surface* screen)
{
	spawner.Render(screen);
	sprite->SetFrame(frame);
	//when dashing fade the sprite based on the dash multiplier
	if (playerMover->IsDashing()) {
		SpriteTransparency::SetTransperency(sprite, screen,
			static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2),
			static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2),
			playerMover->GetDashLinearTime(), frame);
	}
	else {
		SpriteTransparency::SetTransperency(sprite, screen,
			static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2),
			static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2),
			1, frame);
	}




	//debug for player's collider	
	screen->Box(static_cast<int>(pos.x + playerCollider.min.x), static_cast<int>(pos.y + playerCollider.min.y), static_cast<int>(pos.x + playerCollider.max.x), static_cast<int>(pos.y + playerCollider.max.y), 0xffffff);
	//debug for collision with screen borders
	screen->Box(static_cast<int>(pos.x + playerCollider.min.x * 5), static_cast<int>(pos.y + playerCollider.min.y * 5), static_cast<int>(pos.x + playerCollider.max.x * 5), static_cast<int>(pos.y + playerCollider.max.y * 5), 0xffffff);

	auto inactive = std::string("HP: " + std::to_string(hp));

	screen->Print(inactive.c_str(), 10, 40, 0xFF0000);

}

void Player::Update(float deltaTime)
{

	//tries to move tilemap
	playerMover->Update(deltaTime);
	//tilemap is trying to go past the limits
	if (!playerMover->ChangedPos()) {
		//move the player
		playerMover->MovePlayer();
	}

	spawner.Update(deltaTime);
	timer.Update(deltaTime);
}
void Player::TakeDamage(int dg) {
	if (timer.isFinished) {
		Being::TakeDamage(dg);
		timer.ResetVar();
	}

}
void Player::Shoot(bool fire)
{
	spawner.setFlag(fire);
}
void Player::Rotate(int x, int y) {
	//replace with actual pos of player

	MathFunctions::RotateTo(static_cast<float>(x), static_cast<float>(y), pos, dirToFace);


	float angle = MathFunctions::GetDirInAnglesPos(dirToFace);
	//calculate the frame we need to switch for the corresponding angle
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
	return &spawner;
}

const vec2 Player::GetDir() const
{
	return dirToFace;
}

void Player::Die()
{
	std::cout << "RESET GAME";

	Game::Get().ChangeGameState(Tmpl8::Game::GameState::reset);
}

