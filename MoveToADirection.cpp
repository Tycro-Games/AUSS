#include "MoveToADirection.h"
#include "game.h"
using namespace Tmpl8;
MoveToADirection::MoveToADirection(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Collider* col, Callable* call, float speed) :
	Moveable(pos, col, speed),
	dir(dir),
	call(call)
{
	dir->normalize();
}

void MoveToADirection::Update(float deltaTime)
{

	Tmpl8::vec2 nextPos = { 0 };
	nextP = *pos;
	nextPos = (*dir) * speed * deltaTime;


	nextP += nextPos;

	if (col->InGameBounds(nextP, (*col))) {
		if (Game::Get().getTilemap().IsFree(nextP.x, nextP.y))
			(*pos) = nextP;
		else {
			//reflect on obstacle
			colToReflectFrom = Game::Get().getTilemap().GetObstacle(nextP.x, nextP.y)->getColl();

			call->Call();
		}
	}
	else {
		call->Call();
	}


}

MoveToADirection::~MoveToADirection()
{

}
