#include "Projectile.h"

#include "game.h"
#include "MathFunctions.h"
#include "ProjectileSpawner.h"



Projectile::Projectile(const PosDir posDir, Tmpl8::Sprite* _sprite, ProjectileSpawner* spawner)
	:Entity(_sprite, posDir.pos),
	rVar(RotationVar(360 / (static_cast<const float>(_sprite->Frames() - 1)), 90.0f, 20.0f)),
	spawner(spawner),
	collider(COL_MIN, COL_MAX, &pos),
	rot(&pos, &dir, &rVar, &frame, &mover)
{
	collider.type = Collider::Type::projectile;

	mover.Init(&pos, &dir, &collider, std::bind(&Projectile::Reflect, this), SPEED);


	Init(posDir);
}
void Projectile::Init(const PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;
	dir = posDir.dir;
	timer.Init(std::bind(&Projectile::ResetBullet, this), TIME_ALIVE);

	RotateToDirection();
}

Projectile::~Projectile()
{
	sprite = nullptr;//this sprite is deleted by the spawner

}

void Projectile::RotateToDirection()
{
	//rotate to the target dir
	frame = MathFunctions::RotateToDirectionFrames(rVar, dir);
}

void Projectile::Update(const float deltaTime)
{
	if (!getUpdateable())
		return;

	if (collider.toDeactivate)
		ResetBullet();
	mover.Update(deltaTime);
	timer.Update(deltaTime);


}

void Projectile::Render(Tmpl8::Surface* screen)
{

	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x + collider.min.x), static_cast<int>(pos.y + collider.min.y));
#ifdef _DEBUG
	screen->Box(static_cast<int>(pos.x + collider.min.x), static_cast<int>(pos.y + collider.min.y), static_cast<int>(pos.x + collider.max.x), static_cast<int>(pos.y + collider.max.y), 0xff0000);
#endif
}

void Projectile::Reflect()
{
	if (Collider::InGameScreen(pos))
		Tmpl8::Game::Get().PlaySound(SoundID::projectileExplosion);
	if (mover.colToReflectFrom != nullptr) { //reflect on obstacle
		const Collider c = *mover.colToReflectFrom;
		rot.Reflect(Collider::GetNormal(c, collider));

		mover.colToReflectFrom = nullptr;
	}
	else //reflect on screen
		rot.Reflect(Collider::GetNormalEdgeScreen(mover.nextP, collider));
}




void Projectile::ResetBullet()
{
	//trigger the enemy flag for damaging flag
	if (collider.collision)
		if (collider.collision->type == Collider::Type::enemy)
			collider.collision->toDeactivate = true;
	Tmpl8::Game::Get().PlaySound(SoundID::projectileExplosion);
	collider.toDeactivate = false;
	timer.isFinished = true;
	spawner->AddProjectileToPool(this);
	spawner->SpawnExplosions(pos + collider.min);

}
