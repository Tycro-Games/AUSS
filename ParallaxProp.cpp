#include "ParallaxProp.h"



using namespace std;
ParallaxProp::ParallaxProp(const filesystem::path& spritePath, float speed)
	: Entity(spritePath, 1),
	moveInstance(&pos, speed)
{
}


ParallaxProp::~ParallaxProp()
{
}

void ParallaxProp::Init(const Tmpl8::vec2 _pos, float speed)
{
	Entity::Init(_pos);
	moveInstance.Init(&pos, speed);

}

void ParallaxProp::Update(float deltaTime)
{

}

void ParallaxProp::Render(Tmpl8::Surface* screen)
{
	sprite.SetFrame(frame);
	sprite.Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
}

Moveable* ParallaxProp::getMover()
{
	return &moveInstance;
}
