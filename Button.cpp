#include "Button.h"
#include "MathFunctions.h"
#include "game.h"
Button::Button(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, Collider* cursor, Tmpl8::Sprite* unpressed, Tmpl8::Sprite* pressed) :
	//pressedTexture(new Tmpl8::Surface("Build/assets/Play_Pushed.png")),
	Entity(sprite, pos),
	pressedSprite(pressed),
	unpressedSprite(unpressed),
	cursor(cursor),
	col(new Collider(Tmpl8::vec2(0), Tmpl8::vec2(64, 64))),
	offset(32, 32)

{

}

Button::~Button()
{
	delete col;
	delete pressedSprite;
	delete unpressedSprite;
	sprite = NULL;
}



void Button::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	screen->Box(pos->x + col->min.x - offset.x, pos->y + col->min.y - offset.x, pos->x + col->max.x - offset.x, pos->y + col->max.y - offset.y, 0xffffff);
	sprite->Draw(screen, pos->x - offset.x, pos->y - offset.y);
}

void Button::CheckHovering()
{
	isHovering = Collider::Collides(col->At(*pos - offset), cursor->At(*cursor->pos));


	if (isHovering) {

		*sprite = *pressedSprite;
	}
	else
		*sprite = *unpressedSprite;

}





void Button::Update(float deltaTime)
{
	//maybe some animation?
}







