#include "ExitButton.h"
#include "game.h"
#include "SDL.h"
ExitButton::ExitButton(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, Collider* cursor, Tmpl8::Sprite* unpressed, Tmpl8::Sprite* pressed) :
	Button(sprite, pos, cursor, unpressed, pressed)
{
}

ExitButton::~ExitButton()
{
}

void ExitButton::ChangeSprite()
{
	CheckHovering();
	

}



void ExitButton::Update(float deltaTime)
{
	Button::Update(deltaTime);
	if (isHovering && Tmpl8::Game::isPressingLeftMouse)
	{
		SDL_Event quit;
		quit.type = SDL_QUIT;
		//quit.key.keysym.sym = SDL_QuitEvent;
		SDL_PushEvent(&quit);
	}
}

void ExitButton::Render(Tmpl8::Surface* screen)
{
	Button::Render(screen);
}


