#include "EnemyHoarder.h"
#include "MathFunctions.h"
EnemyHoarder::EnemyHoarder(PosDir posDir, Tmpl8::Sprite* sprite, EnemySpawner* spawner) :
	Enemy(new Tmpl8::vec2(posDir.pos), sprite, spawner),
	col(new Collider(COL_MIN, COL_MAX, pos))
{
	dir = new Tmpl8::vec2();
	mover = new MoveToADirection(this->pos, this->dir, col, this, SPEED);
	Init(posDir);
}
//EnemyHoarder::EnemyHoarder(const Enemy& enemy) :
//	Enemy(enemy),
//	col(new Collider(COL_MIN, COL_MAX, pos))
//{
//	dir = new Tmpl8::vec2();
//	mover = new MoveToADirection(this->pos, this->dir, col, this, SPEED);
//
//}



EnemyHoarder::~EnemyHoarder()
{

	delete mover;
}

void EnemyHoarder::Update(float deltaTime)
{
	if (!getUpdateable())
		return;
	RotateToDirection();
	float dist = MathFunctions::GetDistance(*pos, spawner->GetPlayerPos());
	if (dist > MAX_DISTANCE_TO_PLAYER)
		mover->Update(deltaTime);

	//marked by collision
	if (toDeactivate)
		ResetEnemy();
}

void EnemyHoarder::Render(Tmpl8::Surface* screen)
{
	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, pos->x, pos->y);
	screen->Box(pos->x, pos->y, pos->x + rVar.SPRITE_OFFSET, pos->y + rVar.SPRITE_OFFSET, 0xffffff);

}

void EnemyHoarder::RotateToDirection()
{

	//rotate to the target dir
	Tmpl8::vec2 playerPos = spawner->GetPlayerPos();
	MathFunctions::RotateTo(playerPos.x, playerPos.y, *pos, dir);
	frame = MathFunctions::RotateToDirectionFrames(rVar, *dir);

}

void EnemyHoarder::Init(PosDir posDir)
{
	SetActive(true);
	*pos = posDir.pos;
	*dir = posDir.dir;

}



void EnemyHoarder::ResetEnemy()
{
	toDeactivate = false;
	spawner->AddEnemyToPool(this);
}

void EnemyHoarder::Call()
{
	std::cout << "Got to the player";
}