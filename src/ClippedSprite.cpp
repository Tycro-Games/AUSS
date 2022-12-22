#include "ClippedSprite.h"
#include "MathFunctions.h"
using namespace Tmpl8;


void ClippedSprite::DrawSpriteClippedHorizontally(Surface* screen, Surface& sprite, const float linearF, const int x,
	const int y)
{
	Pixel* src = sprite.GetBuffer();
	Pixel* dst = screen->GetBuffer() + x + y * screen->GetPitch();

	const int height = sprite.GetHeight();
	const int width = static_cast<int>(MathFunctions::Lerp(0.0f, static_cast<float>(sprite.GetWidth()), linearF));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//check if the pixel we want to copy is opaque
			if ((src[j] & 0xFF000000) >> 24 == 255)
				dst[j] = src[j];
		}
		src += sprite.GetWidth();
		dst += screen->GetPitch();
	}
}
