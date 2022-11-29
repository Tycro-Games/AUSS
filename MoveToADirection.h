#pragma once
#include "Moveable.h"
#include "MathFunctions.h"
#include "Timer.h"
class MoveToADirection :public Moveable
{
public:
	MoveToADirection(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Collider* col, const Event& call, float speed = 2.0f);
	MoveToADirection();
	void Init(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Collider* col, const Event& call, float speed = 2.0f);

	void Update(float deltaTime)override;
	void ReflectDirection(Tmpl8::vec2 normal) {
		*dir = MathFunctions::Reflect(*dir, normal);

	}
	~MoveToADirection() = default;
	Tmpl8::vec2 nextP;
	Collider* colToReflectFrom = nullptr;
protected:
	const float desiredTime = 1.5f;
	Tmpl8::vec2* dir;
	Event reflect;


};


