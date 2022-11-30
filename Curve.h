#pragma once
#include <functional>

class Curve final
{
public:
    explicit Curve(std::function<float(float)> func, float scale = 1.0f);

    /**
     * Evalaluate the curve and return the evaluated value.
     */
    float evaluate(float x);

    /**
     * Check if we are at the end of the curve.
     */
    bool isAtEnd() const
    {
        return currentValue >= 1.0f;
    }

    void reset()
    {
        currentValue = 0.0f;
    }

    float getScale() const
    {
        return scaleValue;
    }

    float setScale(float scale)
    {
        scaleValue = scale;
    }

private:
    float currentValue = 0.0f;
    float scaleValue = 1.0f;

    std::function<float(float)> parametricCurve;
};
