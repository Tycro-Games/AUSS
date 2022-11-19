#include "Cursor.h"
using namespace Tmpl8;
Cursor::Cursor(const std::filesystem::path& spritePath, Tmpl8::vec2 pos) :
	Entity(spritePath, 1, pos),
	col(Collider(vec2(12, 12), vec2(13, 13), &this->pos))
{
	AddOffset();
}

void Cursor::AddOffset()
{
	pos += offset;
}

Cursor::~Cursor()
{
}

void Cursor::Update(float deltaTime)
{
	//animation maybe?
}

void Cursor::ChangePosition(int x, int y)
{
	pos.x = static_cast<float>(x);
	pos.y = static_cast<float>(y);
	AddOffset();
}

void Cursor::Render(Tmpl8::Surface* screen)
{
	sprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
}
