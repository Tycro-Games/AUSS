#include "Player.h"
#include "MathFunctions.h"
#include "game.h"
#include "Rotator.h"

#include <string>
using namespace Tmpl8;
Player::Player(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, Collider co, Collider* tileMapCol, int hp)
	:dirToFace(new Tmpl8::vec2()),
	Being(sprite, pos, hp),
	startingPos(pos),
	col(Collider(co.min, co.max, &startingPos)),
	map(map),
	tilemapCollider(tileMapCol),
	projectileSprite(new Tmpl8::Sprite(new Tmpl8::Surface("assets/OriginalAssets/phaser.tga"), 16))

{
	spawner = new ProjectileSpawner(&this->pos, -Tmpl8::vec2(rVar.SPRITE_OFFSET / 2, rVar.SPRITE_OFFSET / 2),
		dirToFace,
		projectileSprite,
		new Tmpl8::Sprite(new Tmpl8::Surface("assets/OriginalAssets/smoke.tga"), 10));

	playerMover = new MoveablePlayer(&this->pos, &col, tilemapCollider);
	timer = (new Timer(this, TIME_TO_HIT));
}

Player::~Player()
{
	delete timer;
	delete playerMover;
	delete spawner;
	delete dirToFace;
	delete projectileSprite;

}
Tmpl8::Sprite* copy = new Sprite(new Surface("assets/player.png"), 32);
bool toFadeIn = false;

void Player::FadeOut(Tmpl8::Sprite& sprit, Tmpl8::Surface* screen, float alpha) {
	
	bool hasFaded = true;
	for (int x = 0; x < sprite->GetSurface()->GetPitch(); x++) {
		for (int y = 0; y < sprite->GetHeight(); y++) {
			Pixel pixe = sprite->GetBuffer()[x + y * sprite->GetSurface()->GetPitch()];

			Pixel R = (pixe & RedMask) >> 16;
			Pixel G = (pixe & GreenMask) >> 8;
			Pixel B = (pixe & BlueMask);
			float deltaR = 1 / (255.0f / R);
			float deltaG = 1 / (255.0f / G);
			float deltaB = 1 / (255.0f / B);

			B -= deltaB * alpha;
			R -= deltaR * alpha;
			G -= deltaG * alpha;
			
			Pixel c = R << 16 | G << 8 | B;
			if (c)
				hasFaded = false;
			sprite->GetBuffer()[x + y * sprite->GetSurface()->GetPitch()] = c;
		}
	}
	if (hasFaded)
		toFadeIn = true;

}
void Player::FadeIn(Tmpl8::Sprite& sprit, Tmpl8::Surface* screen, float alpha) {

	for (int x = 0; x < copy->GetSurface()->GetPitch(); x++) {
		for (int y = 0; y < copy->GetHeight(); y++) {
			Pixel pixe = copy->GetBuffer()[x + y * copy->GetSurface()->GetPitch()];

			Pixel R = (pixe & RedMask) >> 16;
			Pixel G = (pixe & GreenMask) >> 8;
			Pixel B = (pixe & BlueMask);
			float deltaR = 1 / (255.0f / R);
			float deltaG = 1 / (255.0f / G);
			float deltaB = 1 / (255.0f / B);

			B -= deltaB * alpha;
			R -= deltaR * alpha;
			G -= deltaG * alpha;
			

			Pixel c = R << 16 | G << 8 | B;
			sprite->GetBuffer()[x + y * sprite->GetSurface()->GetPitch()] = pixe;
		}
	}
}
void Player::Render(Tmpl8::Surface* screen)
{
	spawner->Render(screen);
	sprite->SetFrame(frame);

	if (!toFadeIn)
		FadeOut(*sprite, screen, 1);
	
	if (toFadeIn)
		FadeIn(*sprite, screen, 1);
	sprite->Draw(screen, static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2), static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2));

	//debug for player's collider	
	screen->Box(static_cast<int>(pos.x + col.min.x), static_cast<int>(pos.y + col.min.y), static_cast<int>(pos.x + col.max.x), static_cast<int>(pos.y + col.max.y), 0xffffff);
	//debug for collision with screen borders
	screen->Box(static_cast<int>(pos.x + col.min.x * 5), static_cast<int>(pos.y + col.min.y * 5), static_cast<int>(pos.x + col.max.x * 5), static_cast<int>(pos.y + col.max.y * 5), 0xffffff);

	auto inactive = std::string("HP: " + std::to_string(hp));

	screen->Print(inactive.c_str(), 10, 40, 0xFF0000);
	auto dashing = std::string("Dashing: " + std::to_string(playerMover->IsDashing()));

	screen->Print(dashing.c_str(), 50, 40, 0xFFFF00);
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
	return spawner;
}

void Player::Die()
{
	std::cout << "RESET GAME";

	Tmpl8::Game::ChangeGameState(Tmpl8::Game::GameState::reset);
}

