#include "MathFunctions.h"
#include "RandomNumbers.h"
#include <algorithm>
#include <cassert>
#include <cmath>
using namespace Tmpl8;

float MathFunctions::GetDirInDegreesPositive(const vec2 dir)
{
	float angle = atan2(dir.y, dir.x); //return angle in radians

	angle *= (180 / PI); //convert to angles from radians
	if (angle < 0) //convert to positive angles
	{
		angle = 360 + angle;
	}
	return angle;
}

float MathFunctions::GetDirInDegrees(const vec2 dir)
{
	float angle = atan2(dir.y, dir.x); //return angle in radians

	angle *= (180 / PI); //convert to angles from radians

	return angle;
}

/// <summary>
/// get a vec2 from an angle expressed in radians
/// </summary>
/// <param name="angle"></param>
/// <returns></returns>
vec2 MathFunctions::GetVec2FromRadians(const float angle)
{
	//the coordinate system has up as negative
	return vec2{ (cos(angle)), -(sin(angle)) };
}

float MathFunctions::GetDistance(const vec2 pos1, const vec2 pos2)
{
	const float dx = pos2.x - pos1.x;
	const float dy = pos2.y - pos1.y;
	return sqrtf(dx * dx + dy * dy);
}

float MathFunctions::GetDistanceSqr(const vec2 pos1, const vec2 pos2)
{
	const float dx = pos2.x - pos1.x;
	const float dy = pos2.y - pos1.y;
	return dx * dx + dy * dy;
}


vec2 MathFunctions::Reflect(const vec2 dir, const vec2 norm)
{
	//this is double the projection of the direction onto the normal
	const float dn = 2 * dir.dot(norm);
	//subtract from the original direction so we get the reflected vector
	return dir - norm * dn;
}

void MathFunctions::RotateToDirection(const vec2& newDirection, const vec2& pos, vec2& currentDirection)
{
	currentDirection.x = newDirection.x - pos.x;
	currentDirection.y = newDirection.y - pos.y;

	currentDirection.normalize();
}

unsigned int MathFunctions::RotateToDirectionFrames(const RotationVar& rVar, const vec2& dir)
{
	//return the corresponding frame
	return static_cast<unsigned int>(fmod(GetDirInDegreesPositive(dir) + rVar.OFFSET_SPRITE, 360.0f) / rVar.ANGLE_SIZE);
}

float MathFunctions::DashFunction(float x)
{
	x = Clamp(x, 0.0f, 1.0f);
	return -4 * ((x - .5f) * (x - .5f)) + x / 8 + .875f; //this look like a parabola 
}

vec2 MathFunctions::GetRandomVec2(const float min, const float max, const float deviationMultiplier)
{
	//random direction
	RandomNumbers randomNumbers;
	//random signs
	const bool xNegative = randomNumbers.RandomBetweenInts(0, 2) == 1;
	const bool yNegative = randomNumbers.RandomBetweenInts(0, 2) == 1;
	//into floats that make the vec2
	float x = randomNumbers.RandomBetweenFloats(min, max);
	if (xNegative)
		x *= -1;
	float y = randomNumbers.RandomBetweenFloats(min, max);
	if (yNegative)
		y *= -1;
	//adding multiplier
	x *= deviationMultiplier;
	y *= deviationMultiplier;
	return { x, y };
}

float MathFunctions::Lerp(const float a, const float b, const float f)
{
	assert(0.0f <= f && f <= 1.0f);
	return (1.0f - f) * a + b * f;
}

float MathFunctions::InverseLerp(const float a, const float b, float f)
{
	f = std::clamp(f, a, b);

	return (f - a) / (b - a);
}
