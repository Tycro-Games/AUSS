#include "Button.h"
#include <iostream>
#include "MathFunctions.h"
#include "game.h"
Button::Button(Tmpl8::Sprite* sprite, Collider* cursor) :
	//pressedTexture(new Tmpl8::Surface("Build/assets/Play_Pushed.png")),
	Entity(sprite, new Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2)),
	pressedSprite(new Tmpl8::Sprite(new Tmpl8::Surface("Build/assets/Play_Pushed.png"), 1)),
	cursor(cursor),
	col(new Collider(Tmpl8::vec2(0), Tmpl8::vec2(64, 64))),
	offset(32, 32)

{
	timer = new Timer(this, FADE_SPEED / 1000.0f, true);
}

Button::~Button()
{
	delete timer;
	delete col;
	delete pressedSprite;
}



void Button::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	screen->Box(pos->x + col->min.x - offset.x, pos->y + col->min.y - offset.x, pos->x + col->max.x - offset.x, pos->y + col->max.y - offset.y, 0xffffff);
	sprite->Draw(screen, pos->x - offset.x, pos->y - offset.y);
}
int count = 0;
void Button::Call()
{
	count++;
	std::cout << count << '\n';
	//nice fadeout in 255 calls
	Fade();
}



void Button::Update(float deltaTime)
{
	bool isHovering = Collider::Collides(col->At(*pos - offset), cursor->At(*cursor->pos));
	if (isHovering) {
		//Color the thing in some way

		timer->Update(deltaTime);

		//std::cout << fade << '\n';
	}
	if (isHovering && Tmpl8::Game::isPressingLeftMouse)
	{
		Tmpl8::Game::currentState = Tmpl8::Game::game;
	}
}

void Button::Fade()
{

	for (int x = 0; x < sprite->GetWidth(); x++) {
		for (int y = 0; y < sprite->GetHeight(); y++) {

			Tmpl8::Pixel pixe = sprite->GetBuffer()[x + y * sprite->GetWidth()];

			unsigned char r = (pixe & 0xff0000) >> 16;
			unsigned char g = (pixe & 0x00ff00) >> 8;
			unsigned char b = (pixe & 0x0000ff);
			float deltaR = 1 / (255.0f / r);
			float deltaG = 1 / (255.0f / g);
			float deltaB = 1 / (255.0f / b);

			r -= deltaR;
			g -= deltaG;
			b -= deltaB;
			//std::cout << deltaR << " " << deltaG << " " << deltaB << '\n';
			unsigned int color = (r << 16) | (g << 8) | b;

			sprite->GetBuffer()[x + y * sprite->GetWidth()] = color;
		}
	}
}
