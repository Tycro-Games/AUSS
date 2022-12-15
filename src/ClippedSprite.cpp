#include "ClippedSprite.h"
#include "MathFunctions.h"
using namespace Tmpl8;


void ClippedSprite::DrawSprite(Surface* screen, Surface& sprite, const float linearF, const int posX, const int posY)
{
	//code used for clipping when drawing tiles should be used here
	const int sX = 0;
	const int sY = 0;

	const int x = posX;
	const int y = posY;
	Pixel* src = sprite.GetBuffer() + sX + sY * sprite.GetPitch();
	Pixel* dst = screen->GetBuffer() + x + y * screen->GetPitch();

	const int height = sprite.GetHeight();
	const int width = static_cast<int>(MathFunctions::Lerp(0.0f, static_cast<float>(sprite.GetWidth()), linearF));
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
