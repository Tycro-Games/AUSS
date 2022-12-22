#pragma once
#include "surface.h"
//this could be extended to work as a mask.

//draws a clipped sprite having the left part as a pivot
class ClippedSprite
{
public:
	//Should always receive position to draw that are entirely on-screen.
	static void DrawSpriteClippedHorizontally(Tmpl8::Surface* screen, Tmpl8::Surface& sprite, float linearF, int x,
		int y);
};
