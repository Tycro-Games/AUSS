#pragma once
#include "Subject.h"
#include "Being.h"
#include "ProjectileSpawner.h"
#include "RotationVar.h"
#include "MoveablePlayer.h"
#include "Tilemap.h"
#include "HealthBar.h"


class Player final : public Being, public Followable, public Observer, public Subject
{
public:
	Player();
	~Player() override = default;
	void Init(const Collider& tileMapCollider, const Tmpl8::vec2& _pos);

	void Render(Tmpl8::Surface* screen) override;
	void Update(float deltaTime) override;
	//input calls
	void Shoot(bool fire);
	void Rotate(int x, int y);
	//timer calls
	void Call();
	//being  override
	void TakeDamage(unsigned int) override;
	void Die() override;
	//followable override
	const Tmpl8::vec2 getOffset() override;
	void ResetOffset() override;

	//getters
	MoveablePlayer* getMoveable();
	ProjectileSpawner* getSpawner();
	Tmpl8::vec2 getDir() const;
	Tmpl8::vec2 getPos() const;
	//just returns the x of the max part of the collider
	float getHalfCollider() const;

private:
	RotationVar rVar;
	Tmpl8::vec2 dirToFace;
	Tmpl8::vec2 startingPos;
	//assets
	const std::filesystem::path spriteProjectilePath = "assets/OriginalAssets/phaser.tga";
	const std::filesystem::path spriteExplosionPath = "assets/OriginalAssets/smoke.tga";
	//consts
	const float TIME_TO_HIT = 0.5f;
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-21.0f);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(21.0f);
	//components
	const Collider* tilemapCollider;
	MoveablePlayer playerMover;
	Collider playerCollider;
	ProjectileSpawner spawner;
	Timer cooldownForDamage;
	HealthBar hpBar;
	// Inherited via Observer
	void onNotify(int points, EventType _event) override;
};

inline float Player::getHalfCollider() const
{
	return COL_MAX.x;
}

inline const Tmpl8::vec2 Player::getOffset()
{
	return -pos + lastPos;
}

inline void Player::ResetOffset()
{
	lastPos = pos;
}
