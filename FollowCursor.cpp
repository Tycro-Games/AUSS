#include "FollowCursor.h"

FollowCursor::FollowCursor(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos) :
	Entity(sprite, pos),
	col(new Collider(Tmpl8::vec2(12, 12), Tmpl8::vec2(13, 13), &this->pos))
{
	AddOffset();
}

void FollowCursor::AddOffset()
{
	pos += offset;
}

FollowCursor::~FollowCursor()
{
	delete col;
}

void FollowCursor::Update(float deltaTime)
{

}

void FollowCursor::ChangePosition(int x, int y)
{
	pos.x = x;
	pos.y = y;
	AddOffset();
}

void FollowCursor::Render(Tmpl8::Surface* screen)
{
	screen->Box(pos.x + col->min.x, pos.y + col->min.y, pos.x + col->max.x, pos.y + col->max.y, 0xffffff);
	sprite->Draw(screen, pos.x, pos.y);
}
