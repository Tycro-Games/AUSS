#include "PlayButton.h"
#include "game.h"
using namespace Tmpl8;
PlayButton::PlayButton(Sprite* sprite, vec2 pos, Collider& cursor, Sprite* pressed) :
	Button(sprite, pos, cursor, pressed)
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
	if (isHovering && Game::Get().isPressingLeftMouse)
		ResumeGame();
}

void PlayButton::Render(Surface* screen)
{
	Button::Render(screen);
}

void PlayButton::ResumeGame()
{
	Game::Get().isPressingLeftMouse = false;
	Game::Get().currentState = Game::GameState::game;

}
