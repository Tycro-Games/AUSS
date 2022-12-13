#pragma once
#include "SpriteTransparency.h"
#include "Timer.h"
#include <filesystem>
constexpr float FADE_IN = 2.0f;
constexpr float FADE_OUT = 5.0f;
class FadeInOut
{
public:
	FadeInOut(const Event& ev);
	~FadeInOut() = default;
	void FadeIn();
	void FadeOut();
	void Draw(Tmpl8::Surface* screen);
	void Update(float deltaTime);
	void Init();
private:
	const std::filesystem::path spritePath = "src/assets/UI/FadeSprite.png";
	Tmpl8::Sprite sp;
	Timer fadeIn;
	Timer fadeOut;
	Event toCall;
	SpriteTransparency spriteTransparency;
	float linerF = 0.0f;
	float currenT = 0.0f;
};

