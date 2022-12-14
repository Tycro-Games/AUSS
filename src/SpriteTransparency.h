#pragma once
#include "surface.h"

class SpriteTransparency
{

public:
	static void SetTransparency(Tmpl8::Sprite* _sprite, Tmpl8::Surface* screen, int x, int y, float alpha, unsigned int frame = 0);


};

