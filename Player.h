#pragma once

#include "Being.h"
#include "ProjectileSpawner.h"
#include "RotationVar.h"
#include "MoveablePlayer.h"
#include "Tilemap.h"
#include "SpriteTransparency.h"


class Player :public Being, public Callable, public Followable
{
public:
	Player();
	void Init(const Collider& tilemapCollider, const Tmpl8::vec2& pos);
	~Player();
	void Render(Tmpl8::Surface* screen);
	void Update(float deltaTime);
	void Shoot(bool fire);
	void Rotate(int x, int y);
	virtual void Call()override {};
	virtual void TakeDamage(int) override;
	virtual void Die() override;
	virtual const Tmpl8::vec2 GetOffset() override;
	virtual void ResetOffset() override {
		lastPos = pos;
	}
	//getters
	MoveablePlayer* GetMoveable();
	ProjectileSpawner* GetSpawner();
	const Tmpl8::vec2 GetDir() const;

private:

	RotationVar rVar;
	Tmpl8::vec2 dirToFace;
	Tmpl8::vec2 startingPos;
	//assets
	const std::filesystem::path spriteProjectilePath = "assets/OriginalAssets/phaser.tga";
	const std::filesystem::path spriteExplosionPath = "assets/OriginalAssets/smoke.tga";
	//consts
	const float TIME_TO_HIT = 2.0f;
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-33 / 2 - 5, -33 / 2 - 5);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(33 / 2 + 5, 33 / 2 + 5);
	//components
	const Collider* tilemapCollider;
	MoveablePlayer* playerMover;
	Collider playerCollider;
	ProjectileSpawner spawner;
	Timer timer;

};
inline const Tmpl8::vec2 Player::GetOffset() {
	return   -pos + lastPos;
}






