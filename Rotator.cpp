#include "Rotator.h"
#include "MathFunctions.h"

Rotator::Rotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar rVar, int& frame,MoveToADirection* mover, EnemySpawner* spawner) :
	pos(pos),
	dir(dir),
	rVar(rVar),
	frame(&frame),
	spawner(spawner),
	mover(mover)

{

}
void Rotator::Call() {
	RotateToPlayer();
}
void Rotator::RotateToPlayer()
{
	RotateToDirection(spawner->GetPlayerPos());
}
void Rotator::RotateToDirection(Tmpl8::vec2 Pos)
{

	//rotate to the target dir
	MathFunctions::RotateTo(Pos.x, Pos.y, *pos, dir);
	*frame = MathFunctions::RotateToDirectionFrames(rVar, *dir);

}

void Rotator::Reflect()
{
	Tmpl8::vec2 normal = Collider::GetNormalEdgeScreen(mover->nextP,*mover->getColl());

	mover->OppositeDirection(normal);
	RotateToDirection(*pos+*dir);
}
