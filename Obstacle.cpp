#include "Obstacle.h"

Obstacle::Obstacle(Tmpl8::vec2 p, Collider _collider, size_t index)
	:pos(p),
	Moveable(&pos, new Collider(_collider.min, _collider.max, &pos))

{
}
Obstacle::Obstacle()
	:pos(Tmpl8::vec2(0)),
	Moveable(&pos, new Collider(0, 0, &pos))

{
}

Obstacle::~Obstacle()
{
	delete collider;
}

void Obstacle::Update(float deltaTime)
{

}
