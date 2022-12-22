#pragma once
#include <filesystem>

#include "surface.h"
#include "ClippedSprite.h"
#include "Observer.h"
#include "template.h"
constexpr int SPRITE_OFFSET_X = 42;

class HealthBar final : public Observer
{
public:
	HealthBar();
	void Init();
	void Draw(Tmpl8::Surface* screen);
	void onNotify(int points, EventType eventt) override;

private:
	const std::filesystem::path barPath = "assets/Hearts/PNG/health_bar/health_bar.png";
	const std::filesystem::path decorationPath = "assets/Hearts/PNG/health_bar/health_bar_decoration.png";
	Tmpl8::Sprite bar;
	Tmpl8::Sprite decoration;
	ClippedSprite clipSprite;
	float linearF{};
	const Tmpl8::vec2 position = { 0, 0 };
};
