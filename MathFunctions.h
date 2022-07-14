#pragma once
#include "template.h"
#include <iostream>
class MathFunctions {
public:
	static float GetDirInAnglesPos(Tmpl8::vec2 dir);
	static float GetDirInAnglesNeg(Tmpl8::vec2 dir);
	static Tmpl8::vec2 Reflect(Tmpl8::vec2 dir, Tmpl8::vec2 norm);
	static float Lerp(float a, float b, float f)
	{
		return a + f / (b - a);
	}
	static float InverseLerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}
};
