#include "FollowCursor.h"

FollowCursor::FollowCursor(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos) :
	Entity(sprite, pos)
{
}

FollowCursor::~FollowCursor()
{
}

void FollowCursor::Update(float deltaTime)
{

}

void FollowCursor::ChangePosition(int x, int y)
{
	pos->x = x;
	pos->y = y;
}

void FollowCursor::Render(Tmpl8::Surface* screen)
{
	sprite->Draw(screen, pos->x + offset.x, pos->y + offset.y);
}
