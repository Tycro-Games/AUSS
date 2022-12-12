#pragma once
#include "surface.h"
#include "ClippedSprite.h"
#include "Observer.h"
constexpr int SPRITE_OFFSETX = 42;

class HealthBar :public Observer
{

public:
	HealthBar();
	void Init();
	void Draw(Tmpl8::Surface* screen);
	void onNotify(int points, EventType eventt) override;
private:
	const std::filesystem::path barPath = "src/assets/Hearts/PNG/health_bar/health_bar.png";
	const std::filesystem::path decorationPath = "src/assets/Hearts/PNG/health_bar/health_bar_decoration.png";
	Tmpl8::Sprite bar;
	Tmpl8::Sprite decoration;
	ClippedSprite clipSprite;
	float linearF;
	const Tmpl8::vec2 position = { 0,0 };
};

