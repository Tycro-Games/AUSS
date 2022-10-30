#include "MoveInstance.h"

MoveInstance::MoveInstance(Tmpl8::vec2* pos, float speed) :
	Moveable(pos),
	speedOfParallax(speed)
{

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
