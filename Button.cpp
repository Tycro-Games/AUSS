#include "Button.h"
#include "MathFunctions.h"
#include "game.h"
Button::Button(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, Collider& cursor, Tmpl8::Sprite* pressed) :
	Entity(sprite, pos),
	pressedSprite(pressed),
	cursor(&cursor),
	col(new Collider(Tmpl8::vec2(0), Tmpl8::vec2(64, 64))),
	offset(32, 32)
{

}
Button::~Button()
{
	delete col;
	delete pressedSprite;
}

void Button::Init()
{
	isHovering = false;
}

void Button::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);

	if (!isHovering)
		sprite->Draw(screen, static_cast<int>(pos.x - offset.x), static_cast<int>(pos.y - offset.y));
	else
		pressedSprite->Draw(screen, static_cast<int>(pos.x - offset.x), static_cast<int>(pos.y - offset.y));
}

void Button::CheckHovering()
{
	isHovering = Collider::Collides(col->At(pos - offset), cursor->At(*cursor->pos));
}

void Button::Update(float deltaTime)
{
	//maybe some animation?
}







