#include "MoveToADirection.h"
#include "game.h"
using namespace Tmpl8;
MoveToADirection::MoveToADirection(vec2* pos, vec2* dir, Collider* col, const Event& call, const float speed) :
	Moveable(pos, col, speed),
	dir(dir),
	reflect(call)
{
	dir->normalize();
}

MoveToADirection::MoveToADirection()
	:Moveable(),
	reflect(),
	dir(nullptr)
{
}

void MoveToADirection::Init(vec2* pos, vec2* _dir, Collider* collider, const Event& _call, const float speed)
{
	Moveable::Init(pos, collider, speed);
	dir = _dir;
	reflect = _call;
}

void MoveToADirection::Update(const float deltaTime)
{
	vec2 nextPos = { 0 };
	nextP = *pos;
	nextPos = (*dir) * speed * deltaTime;


	nextP += nextPos;

	if (collider->InGameBounds(nextP, (*collider))) {
		if (Game::Get().getTilemap().IsFreeTile(nextP.x, nextP.y))
			(*pos) = nextP;
		else {
			//reflect on obstacle
			colToReflectFrom = Game::Get().getTilemap().GetObstacle(nextP.x, nextP.y)->getColl();

			reflect();
		}
	}
	else {
		//reflect on edge
		reflect();
	}


}


