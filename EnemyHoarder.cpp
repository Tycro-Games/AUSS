#include "EnemyHoarder.h"
#include "MathFunctions.h"
EnemyHoarder::EnemyHoarder(PosDir posDir, Tmpl8::Sprite* sprite, EnemySpawner* spawner) :
	Enemy(posDir.pos, sprite, spawner),
	randomNumbers()
{
	dg = DG;
	col = (new Collider(COL_MIN, COL_MAX, &pos));
	dir = new Tmpl8::vec2();
	mover = new MoveToADirection(&pos, dir, col, this, SPEED);
	move = mover;
	attack = new Timer(this, TIME_TO_ATTACK, true);
	rotate = new Timer();
	rot = new Rotator(&pos, dir, rVar, &frame, mover, spawner);

	Init(posDir);
}



EnemyHoarder::~EnemyHoarder()
{
	delete dir;
	delete mover;
	delete rotate;
	delete attack;
	delete rot;
}

void EnemyHoarder::Update(float deltaTime)
{
	if (!getUpdateable())
		return;

	rotate->Update(deltaTime);
	//marked by collision
	if (col->toDeactivate) {
		//take damage from the collision if it is from the projectile or block
		if (!spawner->IsEnemy(col->collision)) {
			TakeDamage(DG_TO_TAKE);
		}
		else {
			//interacting with enemy 

		}
		col->toDeactivate = false;

	}
	else {
		mover->Update(deltaTime);

		dist = MathFunctions::GetDistanceSqr(pos, spawner->GetPlayerPos());

		if (dist > MAX_DISTANCE_TO_PLAYER) {
			//not in range
			InRangeToAtack = false;
		}
		else if (dist < MAX_DISTANCE_TO_ATTACK) {
			//in range to atack player
			attack->Update(deltaTime);
			InRangeToAtack = true;
		}
		else
		{
			InRangeToAtack = false;
		}

	}


}

void EnemyHoarder::Render(Tmpl8::Surface* screen)
{
	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
	//screen->Box(pos->x, pos->y, pos->x + rVar.SPRITE_OFFSET, pos->y + rVar.SPRITE_OFFSET, 0xffffff);

}



void EnemyHoarder::Init(PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;
	*dir = posDir.dir;
	hp = 100;
	mover->SetSpeed(SPEED + randomNumbers.RandomBetweenFloats(-30, 100));
	rotate->Init(rot, randomNumbers.RandomBetweenFloats(0.1f, 0.9f), true);
	rot->Call();
}



void EnemyHoarder::ResetEnemy()
{

	spawner->AddEnemyToPool(this);
	spawner->SpawnExplosions(pos);
}

void EnemyHoarder::Call()
{
	//ready to atack and in range
	if (attack->FinishedLoop() && InRangeToAtack) {
		spawner->PlayerTakesDamage(this);
		attack->ResetVar();
		//moves a bit after atacking
		ToMove = true;
	}
	else if (col->collision != NULL) {
		//calculate normal based on https://gamedev.stackexchange.com/questions/136073/how-does-one-calculate-the-surface-normal-in-2d-collisions

		Collider c = *mover->colToReflectFrom;

		Tmpl8::vec2 midPoint = (*c.pos) + Tmpl8::vec2(c.max.x / 2, c.max.y / 2);

		Tmpl8::vec2 dist = pos - midPoint;

		float ex = c.max.x / 2.0f;
		float ey = c.max.y / 2.0f;
		Tmpl8::vec2 BottomLeft = *c.pos + Tmpl8::vec2(0, c.max.y);
		Tmpl8::vec2 BottomRight = *c.pos + c.max;

		Tmpl8::vec2 ux = (BottomRight - BottomLeft).normalized();
		Tmpl8::vec2 uy = (*c.pos - BottomLeft).normalized();

		float distX = dist.dot(ux);
		float distY = dist.dot(uy);

		if (distX > ex)distX = ex;
		else if (distX < -ex)distX = -ex;

		if (distY > ey)distY = ey;
		else if (distY < -ey)distY = -ey;

		Tmpl8::vec2 hitPoint = midPoint + ux * distX + uy * distY;

		Tmpl8::vec2 norm = (pos - hitPoint).normalized();
		rot->Reflect(norm);

		mover->colToReflectFrom = NULL;
	}
	//out of bounds
	else {
		rot->Reflect(Collider::GetNormalEdgeScreen(mover->nextP, *mover->getColl()));
	}

}

void EnemyHoarder::Die()
{
	ResetEnemy();
}
