#include "MoveInstance.h"

MoveInstance::MoveInstance(Tmpl8::vec2* _pos, const float _speed) :
	Moveable(_pos),
	speedOfParallax(_speed)
{
}

MoveInstance::MoveInstance()
{
	speedOfParallax = 1.0f;
}

void MoveInstance::Init(Tmpl8::vec2* _pos, const float _speed)
{
	Moveable::Init(_pos);
	speedOfParallax = _speed;
}


void MoveInstance::Translation(const Tmpl8::vec2 translation)
{
	*pos = *pos + (translation * speedOfParallax);
}

void MoveInstance::Update(float deltaTime)
{
}
