#include "SpriteTransparency.h"



void SpriteTransparency::SetTransparency(Tmpl8::Sprite* _sprite, Tmpl8::Surface* screen, const int X, const int Y, const float alpha, const unsigned int frame)
{
	for (int x = 0; x < _sprite->GetWidth(); x++) {
		for (int y = 0; y < _sprite->GetHeight(); y++) {
			const Tmpl8::Pixel colorSrc = _sprite->GetBuffer()[frame * _sprite->GetWidth() + x + y * _sprite->GetSurface()->GetPitch()];
			const Tmpl8::Pixel colorDst = screen->GetBuffer()[X + x + (y + Y) * screen->GetPitch()];
			//get the alpha of the source
			const float aSrc = static_cast<float>(colorSrc >> 24) / 255.0f * alpha;
			//channels of the source
			const unsigned char rSrc = static_cast<unsigned char>(colorSrc >> 16);
			const unsigned char gSrc = static_cast<unsigned char>(colorSrc >> 8);
			const unsigned char bSrc = static_cast<unsigned char>(colorSrc);

			//channels of the destination
			unsigned char rDst = static_cast<unsigned char>(colorDst >> 16);
			unsigned char gDst = static_cast<unsigned char>(colorDst >> 8);
			unsigned char bDst = static_cast<unsigned char>(colorDst);
			//alpha sub-blending
			rDst = static_cast<unsigned char>(static_cast<float>(rSrc) * aSrc + (1 - aSrc) * static_cast<float>(rDst));
			gDst = static_cast<unsigned char>(static_cast<float>(gSrc) * aSrc + (1 - aSrc) * static_cast<float>(gDst));
			bDst = static_cast<unsigned char>(static_cast<float>(bSrc) * aSrc + (1 - aSrc) * static_cast<float>(bDst));


			const Tmpl8::Pixel c = rDst << 16 | gDst << 8 | bDst;

			screen->GetBuffer()[X + x + (y + Y) * screen->GetPitch()] = c;
		}
	}
}
