#include "PlayButton.h"
#include "game.h"
PlayButton::PlayButton(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, Collider* cursor, Tmpl8::Sprite* unpressed, Tmpl8::Sprite* pressed) :
	Button(sprite, pos, cursor, unpressed, pressed)
{
}

PlayButton::~PlayButton()
{
}



void PlayButton::ChangeSprite()
{
	CheckHovering();
}

void PlayButton::Update(float deltaTime)
{
	Button::Update(deltaTime);
	if (isHovering && Tmpl8::Game::isPressingLeftMouse)
		ResumeGame();
}

void PlayButton::Render(Tmpl8::Surface* screen)
{
	Button::Render(screen);
}

void PlayButton::ResumeGame()
{
	Tmpl8::Game::isPressingLeftMouse = false;
	Tmpl8::Game::currentState = Tmpl8::Game::game;

}
