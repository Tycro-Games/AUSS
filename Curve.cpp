#include "Curve.h"

Curve::Curve(std::function<float(float)> func, float scale)
	: scaleValue{ scale }
	, parametricCurve{ std::move(func) }
{}

float Curve::evaluate(float x)
{
	x = x / scaleValue;
	currentValue += x;
	if (currentValue > 1)
		currentValue = 1.0f;
	return parametricCurve(currentValue);
}

