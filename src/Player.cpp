#include "Player.h"
#include "MathFunctions.h"
#include "game.h"

#include "SpriteTransparency.h"
using namespace Tmpl8;
Player::Player() :
	Being("assets/player.png", 32),
	tilemapCollider(nullptr),
	spawner(-Tmpl8::vec2(rVar.SPRITE_OFFSET / 2, rVar.SPRITE_OFFSET / 2),
		spriteProjectilePath,
		spriteExplosionPath)
{

}

void Player::Init(const Collider& tileMapCollider, const Tmpl8::vec2& _pos)
{

	Being::Init(_pos, 100);
	addObserver(&hpBar);
	hpBar.Init();
	startingPos = _pos;
	playerCollider = Collider(COL_MIN, COL_MAX, &pos);

	tilemapCollider = &tileMapCollider;

	lastPos = _pos;

	cooldownForDamage.Init(std::bind(&Player::Call, this), TIME_TO_HIT);
	spawner.Init();
	playerMover.Init(&pos, &playerCollider, tilemapCollider);
}




void Player::Render(Tmpl8::Surface* screen)
{
	spawner.Render(screen);
	hpBar.Draw(screen);
	sprite->SetFrame(frame);
	//when dashing fade the sprite based on the dash multiplier
	if (playerMover.IsDashing()) {
		SpriteTransparency::SetTransparency(sprite, screen,
			static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2),
			static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2),
			playerMover.GetDashLinearTime(), frame);
	}
	else {
		SpriteTransparency::SetTransparency(sprite, screen,
			static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2),
			static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2),
			1.0f, frame);
	}



#ifdef _DEBUG
	//debug for player's collider	
	screen->Box(static_cast<int>(pos.x + playerCollider.min.x), static_cast<int>(pos.y + playerCollider.min.y), static_cast<int>(pos.x + playerCollider.max.x), static_cast<int>(pos.y + playerCollider.max.y), 0xffffff);
	//debug for collision with screen borders
	screen->Box(static_cast<int>(pos.x + playerCollider.min.x * playerMover.GetEdgeBorderDistance()), static_cast<int>(pos.y + playerCollider.min.y * playerMover.GetEdgeBorderDistance()), static_cast<int>(pos.x + playerCollider.max.x * playerMover.GetEdgeBorderDistance()), static_cast<int>(pos.y + playerCollider.max.y * playerMover.GetEdgeBorderDistance()), 0xffffff);
#endif


}

void Player::Update(const float deltaTime)
{

	//tries to move tilemap
	playerMover.Update(deltaTime);


	spawner.Update(deltaTime);
	cooldownForDamage.Update(deltaTime);
}
void Player::TakeDamage(const unsigned int dg) {
	if (cooldownForDamage.isFinished && !playerMover.IsDashing()) {
		Being::TakeDamage(dg);
		notify(hp, EventType::PlayerTakesDamage);
		cooldownForDamage.ResetVar();
	}

}
void Player::Shoot(const bool fire)
{
	spawner.setFlag(fire);
}
void Player::Rotate(const int x, const int y) {
	//replace with actual pos of player

	MathFunctions::RotateToDirection(
		vec2{ static_cast<float>(x),static_cast<float>(y) },
		pos,
		dirToFace);


	float angle = MathFunctions::GetDirInDegreesPositive(dirToFace);
	//calculate the frame we need to switch for the corresponding angle
	angle += rVar.OFFSET_SPRITE;
	angle = fmodf(angle, 360);
	frame = static_cast<int>(angle / rVar.ANGLE_SIZE);

}

MoveablePlayer* Player::GetMoveable()
{
	return &playerMover;
}
ProjectileSpawner* Player::GetSpawner()
{
	return &spawner;
}

vec2 Player::GetDir() const
{
	return dirToFace;
}

Tmpl8::vec2 Player::GetPos() const
{
	return pos;
}

void Player::onNotify(const int points, const EventType _event)
{

	const unsigned int maximumOfProjectiles = points * 4;

	switch (_event)
	{
	case EventType::EndOfAWave:
		//points are the minimum number of projectiles
		//gets a bonus if the accuracy is at least 25%
		if (spawner.getWaveProjectiles() <= maximumOfProjectiles) {
			const float accuracy = 1.0f - MathFunctions::InverseLerp(static_cast<float>(points), static_cast<float>(maximumOfProjectiles), static_cast<float>(spawner.getWaveProjectiles()));
			//if there is a high accuracy get extra points
			if (accuracy > 0.80f)
				notify(1, EventType::BonusConditions);
			std::cout << "accuracy for this wave is:" << accuracy << '\n';
		}
		spawner.ResetWaveProjectiles();
		break;
	case EventType::PlayerTakesDamage:
		TakeDamage(points);
		break;
	case EventType::EnemyDeath: break;
	case EventType::BonusConditions: break;

	}
}

void Player::Call()
{
	//this gets called when the temporary invincibility ends
}

void Player::Die()
{
	std::cout << "RESET GAME";
	removeObserver(&hpBar);
	Game::Get().ChangeGameState(Tmpl8::Game::GameState::reset);
}

