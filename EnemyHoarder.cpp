#include "EnemyHoarder.h"
#include "MathFunctions.h"
EnemyHoarder::EnemyHoarder(PosDir posDir, Tmpl8::Sprite* sprite, EnemySpawner* spawner) :
	Enemy( posDir.pos, sprite, spawner),
	randomNumbers()
{
	dg = DG;
	col = (new Collider(COL_MIN, COL_MAX, &pos));
	dir = new Tmpl8::vec2();
	mover = new MoveToADirection(&pos, dir, col, this, SPEED);
	attack = new Timer(this, TIME_TO_ATTACK, true);
	rotate = new Timer();
	rot = new Rotator(&pos, dir, rVar, frame,mover, spawner);
	
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
		//take damage of the collision is from the projectile
		if (!spawner->IsEnemy(col->collision)) {
			TakeDamage(DG_TO_TAKE);
		}
		else {
			//interacting with enemy 



		}
		col->toDeactivate = false;

		//add projectile damage
	}
	else {
		 dist = MathFunctions::GetDistanceSqr(pos, spawner->GetPlayerPos());
		 mover->Update(deltaTime);
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
	if (attack->FinishedLoop()&&InRangeToAtack) {
		spawner->PlayerTakesDamage(this);
		attack->ResetVar();
		//moves a bit after atacking
		ToMove = true;
	}
	else {
		rot->Reflect();
	}
	
}

void EnemyHoarder::Die()
{
	ResetEnemy();
}
