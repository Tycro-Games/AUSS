#include "Rotator.h"
#include "MathFunctions.h"

Rotator::Rotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar rVar, unsigned int* frame, MoveToADirection* mover) :
	pos(pos),
	dir(dir),
	rVar(rVar),
	mover(mover),
	frame(frame)

{

}


void Rotator::RotateToDirection(Tmpl8::vec2 Pos)
{

	//rotate to the target dir
	int xPos = static_cast<int>(Pos.x);
	int yPos = static_cast<int>(Pos.y);
	int xpos = static_cast<int>(pos->x);
	int ypos = static_cast<int>(pos->y);

	MathFunctions::RotateTo(Pos.x, Pos.y, *pos, *dir);

	*frame = MathFunctions::RotateToDirectionFrames(rVar, *dir);

}


void Rotator::Reflect(const Tmpl8::vec2 normal)
{


	mover->OppositeDirection(normal);
	RotateToDirection(*pos + *dir);
}
