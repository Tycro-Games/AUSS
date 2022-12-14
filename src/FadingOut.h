#pragma once
#include "Timer.h"
#include <filesystem>

#include "surface.h"

class FadingOut
{
public:
	explicit FadingOut(Event ev);
	~FadingOut() = default;
	void FadeOut() const;
	void Draw(Tmpl8::Surface* screen);
	void Update(float deltaTime);
	void Init();
private:
	constexpr float FADE_OUT = 0.7f;

	const std::filesystem::path spritePath = "assets/UI/FadeSprite.png";
	Tmpl8::Sprite sp;
	Timer fadeOut;
	Event toCall;
	float linerF = 0.0f;
	float currenT = 0.0f;
};

