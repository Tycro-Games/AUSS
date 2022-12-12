#pragma once
#include "surface.h"
#include "template.h"
#include <filesystem>
//draws a clipped sprite having the left part as a pivot
class ClippedSprite
{
public:
	ClippedSprite() = default;
	~ClippedSprite() = default;
	void DrawSprite(Tmpl8::Surface* screen, Tmpl8::Surface& sprite, float linearF, int posX, int posY);
private:

};

