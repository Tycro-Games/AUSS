#pragma once
#include "SpriteTransparency.h"
#include "Timer.h"
#include <filesystem>
constexpr float FADE_OUT = 0.7f;
class FadingOut
{
public:
	FadingOut(const Event& ev);
	~FadingOut() = default;
	void FadeOut();
	void Draw(Tmpl8::Surface* screen);
	void Update(float deltaTime);
	void Init();
private:
	const std::filesystem::path spritePath = "assets/UI/FadeSprite.png";
	Tmpl8::Sprite sp;
	Timer fadeOut;
	Event toCall;
	SpriteTransparency spriteTransparency;
	float linerF = 0.0f;
	float currenT = 0.0f;
};

