#include "Button.h"

Button::Button(Tmpl8::Sprite* sprite) :
	//pressedTexture(new Tmpl8::Surface("Build/assets/Play_Pushed.png")),
	Entity(sprite, new Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2))
{

}

Button::~Button()
{


}



void Button::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	sprite->Draw(screen, pos->x - sprite->GetWidth() / 2, pos->y - sprite->GetWidth() / 2);
}

void Button::Update(float deltaTime)
{
}
