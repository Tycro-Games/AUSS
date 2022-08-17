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

	return dir - norm * dn;

}


void MathFunctions::RotateTo(float x, float y, Tmpl8::vec2* pos, Tmpl8::vec2*& dir)
{

	dir->x = x - pos->x;
	dir->y = y - pos->y;

	dir->normalize();

}

float MathFunctions::DashFunction(float x)
{
	if (x >= 0 && x <= 1)
		return -4 * ((x - .5f) * (x - .5f)) + x / 8 + .875f;//this look like a parabola 
	else {
		return 1;
	}
}
