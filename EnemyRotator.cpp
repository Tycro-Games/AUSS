#include "EnemyRotator.h"
#include "game.h"
using namespace Tmpl8;
EnemyRotator::EnemyRotator(vec2* pos, vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection* mover)
	: Rotator(pos, dir, rVar, frame, mover)
{

}
EnemyRotator::EnemyRotator() :
	Rotator()
{
}
void EnemyRotator::Init(vec2* pos, vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection* mover)
{
	Rotator::Init(pos, dir, rVar, frame, mover);
}
void EnemyRotator::Call() {
	RotateToPlayer();
}
void EnemyRotator::RotateToPlayer()
{
	RotateToDirection(Game::Get().getPlayer().GetPos());
}

