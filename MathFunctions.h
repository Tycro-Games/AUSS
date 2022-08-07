#pragma once
#include "template.h"
#include <iostream>
class MathFunctions {
public:
	static float GetDirInAnglesPos(Tmpl8::vec2 dir);
	static float GetDirInAnglesNeg(Tmpl8::vec2 dir);
	static Tmpl8::vec2 Reflect(Tmpl8::vec2 dir, Tmpl8::vec2 norm);
	///should receive a number between 0 and 1
	static float DashFunction(float);
	static float Lerp(float a, float b, float f)
	{
		return a + f / (b - a);
	}
	static float InverseLerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}
};
