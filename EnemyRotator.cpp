#include "EnemyRotator.h"

EnemyRotator::EnemyRotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection* mover, EnemyWaveSpawner* spawner)
	: Rotator(pos, dir, rVar, frame, mover),
	spawner(spawner)
{

}
EnemyRotator::EnemyRotator() :
	Rotator(),
	spawner(nullptr)
{
}
void EnemyRotator::Init(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection* mover, EnemyWaveSpawner* spawn)
{
	Rotator::Init(pos, dir, rVar, frame, mover);
	spawner = spawn;
}
void EnemyRotator::Call() {
	RotateToPlayer();
}
void EnemyRotator::RotateToPlayer()
{
	RotateToDirection(spawner->GetPlayerPos());
}
EnemyRotator::~EnemyRotator()
{
}
