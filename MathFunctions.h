#pragma once
#include "template.h"
#include <iostream>
#include "RotationVar.h"
#include <cassert>

class MathFunctions
{
public:
	static float GetDirInAnglesPositive(Tmpl8::vec2 dir);
	static float GetDirInAngles(Tmpl8::vec2 dir);
	static Tmpl8::vec2 GetVec2FromAngle(float angle, bool clockWise = false);
	static Tmpl8::vec2 Reflect(Tmpl8::vec2 dir, Tmpl8::vec2 norm);
	//x y coordonates, pos current postion, dir modified by reference
	static void RotateToDirection(const Tmpl8::vec2& newDir, const Tmpl8::vec2& pos, Tmpl8::vec2& dir);
	//helper function for rotating sprites
	static unsigned int  RotateToDirectionFrames(const RotationVar&, const Tmpl8::vec2&);
	//the distance between 2 points
	static float GetDistance(Tmpl8::vec2 pos1, Tmpl8::vec2 pos2);
	//the distance between 2 points without taking the square root
	static float GetDistanceSqr(Tmpl8::vec2 pos1, Tmpl8::vec2 pos2);
	///should receive a number between 0 and 1
	static float DashFunction(const float);
	static Tmpl8::vec2 GetRandomVec2(const float min, const float max, const float deviationMultiplier = 1.5f);

	//source for lerp and inverse lerp https://www.gamedev.net/articles/programming/general-and-gameplay-programming/inverse-lerp-a-super-useful-yet-often-overlooked-function-r5230/
	//f=0, returns a
	//f=0.5 returns the middle of a and b
	//f=1 return b
	static float Lerp(float a, float b, float f)
	{
		assert(0.0f <= f && f <= 1.0f);
		return (1.0f - f) * a + b * f;
	}
	//returns a number from 0 (when f is a) to 1 (when f is b)
	static float InverseLerp(float a, float b, float f)
	{
		assert(a <= f && f <= b);
		return (f - a) / (b - a);
	}


};
