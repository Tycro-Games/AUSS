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
float MathFunctions::GetDistance(Tmpl8::vec2 pos1, Tmpl8::vec2 pos2) {
	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	return sqrtf(dx * dx + dy * dy);
}
float MathFunctions::GetDistanceSqr(Tmpl8::vec2 pos1, Tmpl8::vec2 pos2) {
	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	return dx * dx + dy * dy;
}
//based on https://www.youtube.com/watch?v=naaeH1qbjdQ
Tmpl8::vec2 MathFunctions::Reflect(Tmpl8::vec2 dir, Tmpl8::vec2 norm)
{
	//this is double the projection of the triangle
	float dn = 2 * dir.dot(norm);
	//substract from the original direction so so we get the reflected vector
	return dir - norm * dn;

}

void MathFunctions::RotateTo(float x, float y, Tmpl8::vec2 pos, Tmpl8::vec2*& dir)
{
	if (ValidVec2(static_cast<int>(x),
		static_cast<int>(pos.x),
		static_cast<int>(y),
		static_cast<int>(pos.y)))
		return;
	dir->x = x - pos.x;
	dir->y = y - pos.y;






	dir->normalize();



}

int MathFunctions::RotateToDirectionFrames(RotationVar rVar, Tmpl8::vec2 dir)
{
	//rotate to the target dir and return the corresponding frame
	return static_cast<int>(fmod(MathFunctions::GetDirInAnglesPos(dir) + rVar.OFFSET_SPRITE, 360) / rVar.ANGLE_SIZE);
}

float MathFunctions::DashFunction(float x)
{
	if (x >= 0 && x <= 1)
		return -4 * ((x - .5f) * (x - .5f)) + x / 8 + .875f;//this look like a parabola 
	else {
		return 1;
	}
}


