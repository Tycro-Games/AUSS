#include "ExitButton.h"
#include "game.h"
#include "SDL.h"
using namespace Tmpl8;
ExitButton::ExitButton(Sprite* sprite, vec2 pos, Collider* cursor, Sprite* pressed) :
	Button(sprite, pos, cursor, pressed)
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
	if (isHovering && Game::Get().isPressingLeftMouse)
	{
		SDL_Event quit;
		quit.type = SDL_QUIT;
		//quit.key.keysym.sym = SDL_QuitEvent;
		SDL_PushEvent(&quit);
	}
}

void ExitButton::Render(Surface* screen)
{
	Button::Render(screen);
}


