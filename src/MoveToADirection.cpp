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
	dir(nullptr)
{
}

void MoveToADirection::Init(vec2* _pos, vec2* _dir, Collider* _collider, const Event& _call, const float _speed)
{
	Moveable::Init(_pos, _collider, _speed);
	dir = _dir;
	reflect = _call;
}

void MoveToADirection::Update(const float deltaTime)
{
	nextP = *pos;
	const vec2 nextPos = (*dir) * speed * deltaTime;


	nextP += nextPos;

	if (Collider::InGameBounds(nextP, (*collider))) {
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


