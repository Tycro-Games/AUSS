#include "Obstacle.h"

Obstacle::Obstacle(const Tmpl8::vec2 p, const Collider& _collider)
	:
	Moveable(&posObs, &obsCollider),
	posObs(p),
	obsCollider(_collider.min, _collider.max, &posObs)

{
	obsCollider.type = Collider::Type::obstacle;
}

Obstacle::Obstacle()
	:Moveable(&posObs, &obsCollider),
	posObs(Tmpl8::vec2(0)),
	obsCollider(0, 0, &posObs)

{
	obsCollider.type = Collider::Type::obstacle;
}

Obstacle::~Obstacle() = default;

bool Obstacle::operator==(const Obstacle& ob) const
{
	return static_cast<int>(ob.posObs.x) == static_cast<int>(posObs.x) && static_cast<int>(ob.posObs.y) == static_cast<int>(ob.posObs.y);
}

bool Obstacle::operator!=(const Obstacle& ob) const
{
	//based on the position
	return ob.posObs.x != posObs.x || ob.posObs.y != posObs.y;
}


void Obstacle::Update(float deltaTime)
{

}

void Obstacle::Init(const Tmpl8::vec2 _pos, const Collider& col)
{
	posObs = _pos;
	obsCollider.min = col.min;
	obsCollider.max = col.max;
}
