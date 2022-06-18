#include "MathFunctions.h"

float MathFunctions::GetDirInAnglesPos(Tmpl8::vec2 dir)
{
	float angle = atan2(dir.y, dir.x);//return angle in radians

	angle *= (180 / Tmpl8::PI);//convert to angles from radians
	if (angle < 0) //convert to positive angles
	{
		angle = 360 - (-angle);
	}
	return angle;
}
float MathFunctions::GetDirInAnglesNeg(Tmpl8::vec2 dir)
{
	float angle = atan2(dir.y, dir.x);//return angle in radians

	angle *= (180 / Tmpl8::PI);//convert to angles from radians

	return angle;
}

Tmpl8::vec2 MathFunctions::Reflect(Tmpl8::vec2 dir, Tmpl8::vec2 norm)
{

	float dn = 2 * dir.dot(norm);
	std::cout << dir.x << dir.y << '\n';
	return dir - norm * dn;

}
