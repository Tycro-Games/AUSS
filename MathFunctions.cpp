#include "MathFunctions.h"
#include "RandomNumbers.h"
using namespace Tmpl8;
/// <summary>
/// clamped direction to positive degrees
/// </summary>
/// <param name="dir"></param>
/// <returns></returns>
float MathFunctions::GetDirInAnglesPositive(vec2 dir)
{
	float angle = atan2(dir.y, dir.x);//return angle in radians

	angle *= (180 / PI);//convert to angles from radians
	if (angle < 0) //convert to positive angles
	{
		angle = 360 + angle;
	}
	return angle;
}
/// <summary>
/// unclamped direction to degrees
/// </summary>
/// <param name="dir"></param>
/// <returns></returns>
float MathFunctions::GetDirInAngles(vec2 dir)
{
	float angle = atan2(dir.y, dir.x);//return angle in radians

	angle *= (180 / PI);//convert to angles from radians

	return angle;
}
vec2 MathFunctions::GetVec2FromAngle(float angle)
{
	//conversion to radians
	angle = angle * PI / 180;

	return vec2{ round(sin(angle)) ,round(cos(angle)) };
}
float MathFunctions::GetDistance(vec2 pos1, vec2 pos2) {
	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	return sqrtf(dx * dx + dy * dy);
}
float MathFunctions::GetDistanceSqr(vec2 pos1, vec2 pos2) {
	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	return dx * dx + dy * dy;
}
/// <summary>
/// gives the reflected vector
///based on https://www.youtube.com/watch?v=naaeH1qbjdQ
/// </summary>
/// <param name="dir">direction of the vector</param>
/// <param name="norm">needs to be of length 1</param>
/// <returns></returns>
vec2 MathFunctions::Reflect(vec2 dir, vec2 norm)
{
	//this is double the projection of the direction onto the normal
	float dn = 2 * dir.dot(norm);
	//substract from the original direction so we get the reflected vector
	return dir - norm * dn;

}
/// <summary>
/// changes the currentDirection to the new direction
/// </summary>
/// <param name="newDirection"></param>
/// <param name="pos"></param>
/// <param name="currentDirection"></param>
void MathFunctions::RotateToDirection(const vec2& newDirection, const vec2& pos, vec2& currentDirection)
{

	currentDirection.x = newDirection.x - pos.x;
	currentDirection.y = newDirection.y - pos.y;

	currentDirection.normalize();

}

int MathFunctions::RotateToDirectionFrames(RotationVar rVar, vec2 dir)
{
	//rotate to the target dir and return the corresponding frame
	return static_cast<int>(fmod(MathFunctions::GetDirInAnglesPositive(dir) + rVar.OFFSET_SPRITE, 360) / rVar.ANGLE_SIZE);
}

float MathFunctions::DashFunction(float x)
{
	if (x >= 0 && x <= 1)
		return -4 * ((x - .5f) * (x - .5f)) + x / 8 + .875f;//this look like a parabola 
	else {
		return 1;
	}
}

vec2 MathFunctions::GetRandomVec2(const float min, const float max, const float deviationMultiplier)
{
	//random direction
	RandomNumbers randomNumbers;
	//random signs
	bool xNegative = randomNumbers.RandomBetweenInts(0, 2) == 1;
	bool yNegative = randomNumbers.RandomBetweenInts(0, 2) == 1;
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
	return vec2(x, y);
}


