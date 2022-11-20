#pragma once


//refactoring from Jeremiah's code https://www.youtube.com/watch?v=qbOHI0CRzD4
//it is redundant to have a lot of buttons just to change what function they trigger
#include "AABB.h"
#include "Renderable.h"

//gives functions that can be passed as objects
#include <filesystem>
#include <functional>
enum class ButtonState {
	Default,
	Hover
};
//writing that var name is equivalent to the boiler plate on the right side
using ButtonPressEvent = std::function<void()>;

class Button :public Renderable
{
public:
	Button(const std::filesystem::path& defaultSprite, const std::filesystem::path& pressedSprite, const Tmpl8::vec2& centerPos, const ButtonPressEvent& ev);
	//default the deconstructor means that it does not need implementation for the base class
	virtual ~Button() = default;
	void Render(Tmpl8::Surface* screen) override;
	//input functions
	void OnMouseMoved(int x, int y);
	void OnMouseUp(int button);

	ButtonState GetState()const {
		return state;
	}
private:
	//the variables need to be declared in the order they are constructed in the initializer list
	Tmpl8::Sprite defaultSprite;
	Tmpl8::Sprite pressedSprite;


	Tmpl8::vec2 centerPos;
	Tmpl8::vec2 mousePos;

	//variable that can store a function with no arguments that returns void
	std::function<void()> onPress;

	ButtonState state;
	AABB aabb;

	int offsetX, offsetY;
};

