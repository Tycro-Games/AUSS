#include "MathFunctions.h"
#include "Rotator.h"

Rotator::Rotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar rVar, int& frame, EnemySpawner* spawner) :
	pos(pos),
	dir(dir),
	rVar(rVar),
	frame(&frame),
	spawner(spawner)
{

}
void Rotator::Call() {
	RotateToDirection(spawner->GetPlayerPos());
}
void Rotator::RotateToDirection(Tmpl8::vec2 Pos)
{

	//rotate to the target dir

	MathFunctions::RotateTo(Pos.x, Pos.y, *pos, dir);
	*frame = MathFunctions::RotateToDirectionFrames(rVar, *dir);

}