#include "Cursor.h"
using namespace Tmpl8;
Cursor::Cursor(const std::filesystem::path& spritePath, const vec2 _pos) :
	Entity(spritePath, 1, pos),
	col(Collider(vec2(12, 12), vec2(13, 13), &this->pos))
{
	AddOffset();
}

void Cursor::AddOffset()
{
	pos += offset;
}

Cursor::~Cursor() = default;

void Cursor::Update(float deltaTime)
{
	//animation maybe?
}

void Cursor::ChangePosition(const int x, const int y)
{
	pos.x = static_cast<float>(x);
	pos.y = static_cast<float>(y);
	AddOffset();
}

void Cursor::Render(Surface* screen)
{
	sprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
}
