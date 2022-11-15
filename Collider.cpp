#include "Collider.h"
#include "game.h"
using namespace Tmpl8;
Collider::Collider(vec2 min, vec2 max) :
	min(min),
	max(max),
	pos(0),
	collision()
{
}

Collider::Collider(vec2 min, vec2 max, vec2* pos) :
	min(min),
	max(max),
	collision(),
	pos(pos)
{
}

Collider::Collider() :
	min(0),
	max(0),
	collision(),
	pos(0)
{
}
vec2 Collider::GetNormal(const Collider& obstacle, const Collider& source)
{
	vec2 midPoint = (*obstacle.pos) + vec2(obstacle.max.x / 2, obstacle.max.y / 2);

	vec2 dist = (*source.pos) - midPoint;

	float ex = obstacle.max.x / 2.0f;
	float ey = obstacle.max.y / 2.0f;

	vec2 BottomLeft = (*obstacle.pos) + vec2(0, obstacle.max.y);
	vec2 BottomRight = (*obstacle.pos) + obstacle.max;

	vec2 ux = (BottomRight - BottomLeft).normalized();
	//obstacle is a collider with the pivot in the top left
	vec2 uy = ((*obstacle.pos) - BottomLeft).normalized();

	float distX = dist.dot(ux);
	float distY = dist.dot(uy);

	if (distX > ex)distX = ex;
	else if (distX < -ex)distX = -ex;

	if (distY > ey)distY = ey;
	else if (distY < -ey)distY = -ey;

	vec2 hitPoint = midPoint + ux * distX + uy * distY;
	vec2 norm = ((*source.pos) - hitPoint).normalized();
	return norm;
}
//checks with the current pos
bool Collider::InGameBounds(Collider& col) {
	return col.Collides(Game::Get().tileMap.GetGameBounds());
}
//checks with the position parameter
bool Collider::InGameBounds(vec2& pos, Collider& col)
{
	return Overlaps(col.At(pos), Game::Get().tileMap.GetGameBounds());

}

vec2 Collider::GetNormalEdgeScreen(const vec2& pos, const Collider& col)
{
	vec2 normal;
	Collider gameBounds = Game::Get().tileMap.GetGameBounds();
	if (pos.x + col.min.x < gameBounds.min.x || pos.x + col.max.x > gameBounds.max.x)
		normal = vec2(1, 0);
	else//if (pos.y + col.min.y < gameBounds.min.y || pos.y + col.max.y < gameBounds.max.y)
		normal = vec2(0, 1);
	return normal;
}

Collider::~Collider()
{
}


