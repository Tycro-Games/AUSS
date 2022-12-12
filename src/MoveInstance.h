#pragma once
#include "Moveable.h"
class MoveInstance :public Moveable
{
public:
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="">position</param>
	/// <param name="speed">the speed of the parallax</param>
	MoveInstance(Tmpl8::vec2*, float speed = 1.0f);
	MoveInstance();

	void Init(Tmpl8::vec2*, float speed = 1.0f);
	~MoveInstance();
	void Translation(const Tmpl8::vec2) override;


private:
	float speedOfParallax;

	// Inherited via Moveable
	void Update(float deltaTime) override;

};




