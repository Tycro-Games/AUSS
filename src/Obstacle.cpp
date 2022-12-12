#include "Obstacle.h"

Obstacle::Obstacle(const Tmpl8::vec2 p, const Collider& _collider)
	:
	Moveable(&pos, &obsCollider),
	pos(p),
	obsCollider(_collider.min, _collider.max, &pos)

{
	obsCollider.type = Collider::Type::Obstacle;
}

Obstacle::Obstacle()
	:pos(Tmpl8::vec2(0)),
	obsCollider(0, 0, &pos),
	Moveable(&pos, &obsCollider)

{
	obsCollider.type = Collider::Type::Obstacle;
}



void Obstacle::Update(float deltaTime)
{

}

void Obstacle::Init(const Tmpl8::vec2 _pos, const Collider& col)
{
	pos = _pos;
	obsCollider.min = col.min;
	obsCollider.max = col.max;
}
