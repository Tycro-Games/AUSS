#include "MoveInstance.h"

MoveInstance::MoveInstance(Tmpl8::vec2* pos, float speed) :
	Moveable(pos),
	speedOfParallax(speed)
{

}

MoveInstance::MoveInstance()
{
	speedOfParallax = 1.0f;
}

void MoveInstance::Init(Tmpl8::vec2* pos, float speed)
{
	Moveable::Init(pos);
	speedOfParallax = speed;
}

MoveInstance::~MoveInstance()
{
}

void MoveInstance::Translation(const Tmpl8::vec2 translation)
{
	*pos = *pos + (translation * speedOfParallax);

}

void MoveInstance::Update(float deltaTime)
{
}
