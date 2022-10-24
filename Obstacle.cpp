#include "Obstacle.h"

Obstacle::Obstacle(Tmpl8::vec2 p, Collider co, size_t index)
	:pos(p),
	Moveable(&pos, new Collider(co.min, co.max, &pos))

{
}
Obstacle::Obstacle()
	:pos(Tmpl8::vec2(0)),
	Moveable(&pos, new Collider(0, 0, &pos))

{
}

Obstacle::~Obstacle()
{
	delete col;
}

void Obstacle::Update(float deltaTime)
{
	
}
