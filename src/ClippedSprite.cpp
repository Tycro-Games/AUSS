#include "ClippedSprite.h"
#include "MathFunctions.h"
using namespace Tmpl8;


void ClippedSprite::DrawSprite(Tmpl8::Surface* screen, Tmpl8::Surface& sprite, float linearF, int posX, int posY)
{
	//code used for clipping when drawing tiles should be used here
	int sX = 0;
	int sY = 0;

	int x = posX;
	int y = posY;
	Pixel* src = sprite.GetBuffer() + sX + sY * sprite.GetPitch();
	Pixel* dst = screen->GetBuffer() + x + y * screen->GetPitch();

	int height = sprite.GetHeight();
	int width = static_cast<int>(MathFunctions::Lerp(0.0f, static_cast<float>(sprite.GetWidth()), linearF));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {

			//check if the pixel we want to copy is opaque
			if ((src[j] & 0xFF000000) >> 24 == 255)
				dst[j] = src[j];

		}
		src += sprite.GetWidth();
		dst += screen->GetPitch();

	}
}
