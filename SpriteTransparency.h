#pragma once
#include "surface.h"

class SpriteTransparency
{

public:
	SpriteTransparency(Tmpl8::Surface*);
	~SpriteTransparency();
	void SetTransperency(Tmpl8::Sprite* sprit, Tmpl8::Surface* screen, int x, int y, float alpha, unsigned int frame = 0);





private:
	Tmpl8::Surface* copy = nullptr;
};

