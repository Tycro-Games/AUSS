#include "MathFunctions.h"

float MathFunctions::GetDirInAngles(Tmpl8::vec2 dir)
{
	float angle = atan2(dir.y, dir.x);//return angle in radians

	angle *= (180 / Tmpl8::PI);//convert to angles from radians
	if (angle < 0) //convert to positive angles
	{
		angle = 360 - (-angle);
	}
	return angle;
}
