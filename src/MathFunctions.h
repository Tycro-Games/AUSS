#pragma once
#include "template.h"
#include "RotationVar.h"

class MathFunctions
{
public:
	/// <summary>
	/// clamped direction to positive degrees
	/// </summary>
	/// <param name="dir">Direction to be calculate angles from.</param>
	/// <returns> Angles in positive degrees</returns>
	static float GetDirInDegreesPositive(Tmpl8::vec2 dir);
	/// <summary>
	/// not clamped direction to degrees
	/// </summary>
	/// <param name="dir">Direction to be calculate angles from.</param>
	/// <returns> Angles in degrees (can be negative).</returns>
	static float GetDirInDegrees(Tmpl8::vec2 dir);
	/**
	 * \brief Gives the direction from the specified angle.
	 * \param angle Angle in radians.
	 * \return A vector that points in the corresponding direction to the angle.
	 */
	static Tmpl8::vec2 GetVec2FromRadians(float angle);
	///based on https://www.youtube.com/watch?v=naaeH1qbjdQ

	/**
	 * \brief Reflects the direction based on the normal.
	 * \param dir Vector of magnitude of 1 to be reflected.
	 * \param norm The normal vector from which the reflected vector will pivot.
	 * \return The reflected vector.
	 */
	static Tmpl8::vec2 Reflect(Tmpl8::vec2 dir, Tmpl8::vec2 norm);
	/// <summary>
	/// Changes the currentDirection to the new direction.
	/// </summary>
	/// <param name="newDirection"></param>
	/// <param name="pos"></param>
	/// <param name="currentDirection"></param>
	static void RotateToDirection(const Tmpl8::vec2& newDirection, const Tmpl8::vec2& pos,
		Tmpl8::vec2& currentDirection);
	//helper function for rotating sprites
	static unsigned int RotateToDirectionFrames(const RotationVar&, const Tmpl8::vec2&);
	//the distance between 2 points
	static float GetDistance(Tmpl8::vec2 pos1, Tmpl8::vec2 pos2);
	//the distance between 2 points without taking the square root
	static float GetDistanceSqr(Tmpl8::vec2 pos1, Tmpl8::vec2 pos2);
	/**
	 * \brief Gives the the value of the curve that makes up the dash speed.
	 * \param x A float between 0 and 1.
	 * \return The dash speed at that interpolated factor.
	 */
	static float DashFunction(float x);
	static Tmpl8::vec2 GetRandomVec2(float min, float max, float deviationMultiplier = 1.5f);

	//source for lerp and inverse lerp https://www.gamedev.net/articles/programming/general-and-gameplay-programming/inverse-lerp-a-super-useful-yet-often-overlooked-function-r5230/

	//f=0 returns a
	//f=0.5 returns the middle of a and b
	//f=1 return b
	static float Lerp(float a, float b, float f);
	//returns a number from 0 (when f is a) to 1 (when f is b)
	static float InverseLerp(float a, float b, float f);
};
