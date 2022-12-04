#include "Collider.h"
#include "game.h"
using namespace Tmpl8;
Collider::Collider(vec2 min, vec2 max) :
	min(min),
	max(max),
	pos(0),
	collision()
{
	type = Type::Nothing;
}

Collider::Collider(vec2 min, vec2 max, vec2* pos) :
	min(min),
	max(max),
	collision(),
	pos(pos)
{
	type = Type::Nothing;

}

Collider::Collider() :
	min(0),
	max(0),
	collision(),
	pos(0)
{
	type = Type::Nothing;

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

bool Collider::ClipLine(bool clipX, const Collider& rectangle, const Tmpl8::vec2& v0, const Tmpl8::vec2& v1, float& low, float& high)
{
	//axis low and high
	float dLow, dHigh;
	if (clipX) { //clamp on x
		dLow = (rectangle.min.x - v0.x) / (v1.x - v0.x);
		dHigh = (rectangle.max.x - v0.x) / (v1.x - v0.x);
	}
	else {//clamp on y
		dLow = (rectangle.min.y - v0.y) / (v1.y - v0.y);
		dHigh = (rectangle.max.y - v0.y) / (v1.y - v0.y);
	}
	if (dLow > dHigh)//make sure that the low is low and high is high
		std::swap(dLow, dHigh);

	if (dHigh < low)//no coolision
		return false;
	if (dLow > high)//no coolision
		return false;
	//clamp the values to the intersection interval
	low = std::max(dLow, low);
	high = std::min(dHigh, high);
	if (low > high)//no collision
		return false;
	return true;
}
bool Collider::LineRectangleIntersection(const Tmpl8::vec2& v0, const Tmpl8::vec2& v1, const Collider& rect, Tmpl8::vec2& outputIntersection, float& outpuFraction)
{
	//these are the clamping of the line based on the rectangle
	float fLow = 0.0f;
	float fHigh = 1.0f;

	// check intersection on x
	if (!ClipLine(true, rect, v0, v1, fLow, fHigh)) {
		return false;
	}
	// check intersection on y

	if (!ClipLine(false, rect, v0, v1, fLow, fHigh)) {
		return false;
	}
	vec2 b = v1 - v0;
	//vector where the intersection happened
	outputIntersection = v0 + b * fLow;
	outpuFraction = fLow;
	return true;
}
//checks with the current pos
bool Collider::InGameBounds(Collider& col) {
	return col.Collides(Game::Get().getTilemap().GetGameBounds());
}
//checks with the position parameter
bool Collider::InGameBounds(const vec2& pos, Collider& col)
{
	return Overlaps(col.At(pos), Game::Get().getTilemap().GetGameBounds());

}

vec2 Collider::GetNormalEdgeScreen(const vec2& pos, const Collider& col)
{
	vec2 normal;
	Collider gameBounds = Game::Get().getTilemap().GetGameBounds();
	if (pos.x + col.min.x < gameBounds.min.x || pos.x + col.max.x > gameBounds.max.x)
		normal = vec2(1, 0);
	else//if (pos.y + col.min.y < gameBounds.min.y || pos.y + col.max.y < gameBounds.max.y)
		normal = vec2(0, 1);
	return normal;
}



