#pragma once
#include "surface.h"

class SpriteTransparency
{

public:
	SpriteTransparency();
	~SpriteTransparency();
	static void SetTransperency(Tmpl8::Sprite* sprit, Tmpl8::Surface* screen, int x, int y, float alpha, unsigned int frame = 0);





private:
};

