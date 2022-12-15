#include "Button.h"
#include "game.h"
using namespace Tmpl8;
using namespace std;
Button::Button(const filesystem::path& _defaultSprite, const filesystem::path& _pressedSprite, const vec2& _centerPos, const ButtonPressEvent& ev)
	:
	defaultSprite(new Surface(_defaultSprite.string().c_str()), 1),
	pressedSprite(new Surface(_pressedSprite.string().c_str()), 1),
	centerPos(_centerPos),
	mousePos(0.0f),
	onPress(ev),
	state(ButtonState::Default)

{
	aabb.min = vec2(centerPos.x - static_cast<float>(defaultSprite.GetWidth()) / 2.0f,
		centerPos.y - static_cast<float>(defaultSprite.GetWidth()) / 2.0f);
	aabb.max = vec2(centerPos.x + static_cast<float>(defaultSprite.GetHeight()) / 2.0f,
		centerPos.y + static_cast<float>(defaultSprite.GetHeight()) / 2.0f);

	offsetX = static_cast<int>(centerPos.x - static_cast<float>(defaultSprite.GetWidth()) / 2.0f);
	offsetY = static_cast<int>(centerPos.y - static_cast<float>(defaultSprite.GetHeight()) / 2.0f);

}
void Button::Render(Surface* screen)
{
	if (state == ButtonState::Disabled)
		return;
	switch (state)
	{
	case ButtonState::Default:
		defaultSprite.Draw(screen, offsetX, offsetY);
		break;
	case ButtonState::Hover:
		pressedSprite.Draw(screen, offsetX, offsetY);
		break;
	case ButtonState::Disabled: break;

	}
}

void Button::OnMouseMoved(const int x, const int y)
{
	if (ButtonState::Disabled == state)
		return;



	mousePos = vec2{ static_cast<float>(x),static_cast<float>(y) };

	if (aabb.IsColliding(mousePos)) {
		if (state != ButtonState::Hover) {
			Game::Get().PlaySound(SoundID::hoverUi);
			state = ButtonState::Hover;
		}
	}
	else {
		state = ButtonState::Default;
	}
}

void Button::OnMouseUp(int button) const
{
	switch (state)
	{

	case ButtonState::Hover:
		onPress();
		Game::Get().PlaySound(SoundID::clickUi);

		break;
	case ButtonState::Default: break;
	case ButtonState::Disabled: break;

	}
}
