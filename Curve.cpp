#include "Curve.h"

Curve::Curve(std::function<float(float)> func, float scale)
    : scaleValue{scale}
    , parametricCurve{std::move(func)}
{}

float Curve::evaluate(float x)
{
    x = x / scaleValue;
    currentValue += x;

    return parametricCurve(currentValue);
}

