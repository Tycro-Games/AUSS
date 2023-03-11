#include "Physics.h"


#include "game.h"

using namespace Tmpl8;

bool Physics::Overlaps(const Collider& a, const Collider& b)
{
	return a.min.x > b.min.x && a.min.y > b.min.y
		&& a.max.x < b.max.x && a.max.y < b.max.y;
}

bool Physics::Contains(const Collider& a, const vec2& b)
{
	return a.min.x + a.pos->x < b.x && a.min.y + a.pos->y < b.y
		&& b.x < a.max.x + a.pos->x && b.y < a.max.y + a.pos->y;
}

bool Physics::CollidesY(const Collider& a, const Collider& b)
{
	return a.min.y < b.max.y && a.max.y > b.min.y;
}

bool Physics::CollidesX(const Collider& a, const Collider& b)
{
	return a.min.x < b.max.x && a.max.x > b.min.x;
}


vec2 Physics::GetNormal(const Collider& obstacle, const Collider& source)
{
	const vec2 midPoint = (*obstacle.pos) + vec2(obstacle.max.x / 2, obstacle.max.y / 2);

	const vec2 dist = (*source.pos) - midPoint;

	const float ex = obstacle.max.x / 2.0f;
	const float ey = obstacle.max.y / 2.0f;

	const vec2 bottomLeft = (*obstacle.pos) + vec2(0, obstacle.max.y);
	const vec2 bottomRight = (*obstacle.pos) + obstacle.max;

	const vec2 ux = (bottomRight - bottomLeft).normalized();
	//obstacle is a collider with the pivot in the top left
	const vec2 uy = ((*obstacle.pos) - bottomLeft).normalized();

	float distX = dist.dot(ux);
	float distY = dist.dot(uy);

	if (distX > ex)distX = ex;
	else if (distX < -ex)distX = -ex;

	if (distY > ey)distY = ey;
	else if (distY < -ey)distY = -ey;

	const vec2 hitPoint = midPoint + ux * distX + uy * distY;
	const vec2 norm = ((*source.pos) - hitPoint).normalized();
	return norm;
}

bool Physics::ClipLineOnOneAxis(const bool clipX, const Collider& rectangle, const vec2& v0, const vec2& v1, float& low,
	float& high)
{
	// low and high parts of the interval for this axis
	float dLow, dHigh;
	if (clipX)
	{
		//clamp on x
		dLow = (rectangle.min.x - v0.x) / (v1.x - v0.x);
		dHigh = (rectangle.max.x - v0.x) / (v1.x - v0.x);
	}
	else
	{
		//clamp on y
		dLow = (rectangle.min.y - v0.y) / (v1.y - v0.y);
		dHigh = (rectangle.max.y - v0.y) / (v1.y - v0.y);
	}
	if (dLow > dHigh) //make sure that the low is low and high is high
		std::swap(dLow, dHigh);

	if (dHigh < low) //not intersecting with the interval, too low
		return false;
	if (dLow > high) //not intersecting with the interval, too high
		return false;
	//clamp the values to the intersection interval
	low = std::max(dLow, low);
	high = std::min(dHigh, high);

	//no collision

	return low <= high;
}

bool Physics::LineRectangleIntersection(const vec2& v0, const vec2& v1, const Collider& rect, vec2& outputIntersection,
	float& outputFraction)
{
	//these are the clamping of the line based on the rectangle
	float fLow = 0.0f;
	float fHigh = 1.0f;

	// check intersection on x
	if (!ClipLineOnOneAxis(true, rect, v0, v1, fLow, fHigh))
	{
		return false;
	}
	// check intersection on y
	if (!ClipLineOnOneAxis(false, rect, v0, v1, fLow, fHigh))
	{
		return false;
	}

	const vec2 b = v1 - v0;
	//point where the intersection happened
	outputIntersection = v0 + b * fLow;
	outputFraction = fLow;
	return true;
}

bool Physics::InGameScreen(const vec2& _offset, const Collider& collider)
{
	return _offset.x + collider.min.x >= 0 && _offset.y + collider.min.y >= 0
		&& _offset.x + collider.max.x <= ScreenWidth - 1 && _offset.y + collider.max.y <= ScreenHeight - 1;
}

bool Physics::InGameScreen(const vec2& position)
{
	return position.x >= 0 && position.y >= 0
		&& position.x <= ScreenWidth - 1 && position.y <= ScreenHeight - 1;
}

bool Physics::InGameBounds(const Collider& collider)
{
	return collider.Collides(Game::Get().getTilemap().GetGameBounds());
}

bool Physics::InGameBounds(const vec2& _offset, const Collider& collider)
{
	return Overlaps(collider.At(_offset), Game::Get().getTilemap().GetGameBounds());
}

vec2 Physics::GetNormalEdgeScreen(const vec2& _offset, const Collider& collider)
{
	vec2 normal;
	const Collider gameBounds = Game::Get().getTilemap().GetGameBounds();
	if (_offset.x + collider.min.x < gameBounds.min.x || _offset.x + collider.max.x > gameBounds.max.x)
		normal = vec2(1, 0);
	else //if (posObs.y + collider.min.y < gameBounds.min.y || posObs.y + collider.max.y < gameBounds.max.y)
		normal = vec2(0, 1);
	return normal;
}
