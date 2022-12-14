// ReSharper disable All
#include "Collider.h"
#include "game.h"
using namespace Tmpl8;
Collider::Collider(vec2 min, vec2 max) :
	min(min),
	max(max),
	pos(0),
	collision()
{
	type = Type::nothing;
}

Collider::Collider(vec2 min, vec2 max, vec2* pos) :
	min(min),
	max(max),
	pos(pos),
	collision()
{
	type = Type::nothing;

}

Collider::Collider() :
	min(0),
	max(0),
	pos(0),
	collision()
{
	type = Type::nothing;

}

Collider Collider::operator*(const float multiplier)
{
	min *= multiplier;
	max *= multiplier;
	return {min, max};
}

Collider Collider::At(const Tmpl8::vec2& offset) const
{
	return {min + offset, max + offset};
}

bool Collider::Collides(const Collider& col) const
{
	return Collides(this->At(*pos), col);
}

bool Collider::Collides(const Collider& a, const Collider& b)
{
	return a.min.x <= b.max.x && a.max.x >= b.min.x &&
		a.min.y <= b.max.y && a.max.y >= b.min.y;
}

bool Collider::Overlaps(const Collider& a, const Collider& b)
{

	return a.min.x > b.min.x && a.min.y > b.min.y
		&& a.max.x < b.max.x&& a.max.y < b.max.y;

}

bool Collider::Contains(const Collider& a, const Tmpl8::vec2& b)
{
	/*float xP = round(b.x);
		float yP = round(b.y);
		float Left = round(a.min.x + a.pos->x);
		float Right = round(a.max.x + a.pos->x);
		float Up = round(a.min.y + a.pos->y);
		float Down = round(a.max.y + a.pos->y);
		return xP >= Left && yP >= Up
			&& xP <= Right - 1 && yP <= Down - 1;*/
	return a.min.x + a.pos->x < b.x&& a.min.y + a.pos->y < b.y
		&& b.x < a.max.x + a.pos->x && b.y < a.max.y + a.pos->y;
}

bool Collider::CollidesY(const Collider& a, const Collider& b)
{
	return a.min.y < b.max.y&& a.max.y > b.min.y;

}

bool Collider::CollidesX(const Collider& a, const Collider& b)
{

	return a.min.x < b.max.x&& a.max.x > b.min.x;

}

Collider::~Collider()
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

bool Collider::ClipLineOnOneAxis(bool clipX, const Collider& rectangle, const Tmpl8::vec2& v0, const Tmpl8::vec2& v1, float& low, float& high)
{
	// low and high parts of the interval for this axis
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

	if (dHigh < low)//not intersecting with the interval, too low
		return false;
	if (dLow > high)//not intersecting with the interval, too high
		return false;
	//clamp the values to the intersection interval
	low = std::max(dLow, low);
	high = std::min(dHigh, high);

	//no collision

	return low <= high;
}

bool Collider::LineRectangleIntersection(const Tmpl8::vec2& v0, const Tmpl8::vec2& v1, const Collider& rect, Tmpl8::vec2& outputIntersection, float& outputFraction)
{
	//these are the clamping of the line based on the rectangle
	float fLow = 0.0f;
	float fHigh = 1.0f;

	// check intersection on x
	if (!ClipLineOnOneAxis(true, rect, v0, v1, fLow, fHigh)) {
		return false;
	}
	// check intersection on y
	if (!ClipLineOnOneAxis(false, rect, v0, v1, fLow, fHigh)) {
		return false;
	}

	const vec2 b = v1 - v0;
	//point where the intersection happened
	outputIntersection = v0 + b * fLow;
	outputFraction = fLow;
	return true;
}
//checks with the current pos
bool Collider::InGameBounds(const Collider& col) {
	return col.Collides(Game::Get().getTilemap().GetGameBounds());
}
//checks with the position parameter
bool Collider::InGameBounds(const vec2& pos, const Collider& col)
{
	return Overlaps(col.At(pos), Game::Get().getTilemap().GetGameBounds());

}

vec2 Collider::GetNormalEdgeScreen(const vec2& pos, const Collider& col)
{
	vec2 normal;
	const Collider gameBounds = Game::Get().getTilemap().GetGameBounds();
	if (pos.x + col.min.x < gameBounds.min.x || pos.x + col.max.x > gameBounds.max.x)
		normal = vec2(1, 0);
	else//if (pos.y + col.min.y < gameBounds.min.y || pos.y + col.max.y < gameBounds.max.y)
		normal = vec2(0, 1);
	return normal;
}



