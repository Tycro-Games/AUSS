#include "SpriteTransparency.h"

SpriteTransparency::SpriteTransparencyTmpl8::Surface* sprite)
	
{
	
}

SpriteTransparency::~SpriteTransparency()
{
	
}

void SpriteTransparency::SetTransperency(Tmpl8::Sprite* sprit, Tmpl8::Surface* screen, int X, int Y, float alpha, unsigned int frame)
{
	for (int x = 0; x < sprit->GetWidth(); x++) {
		for (int y = 0; y < sprit->GetHeight(); y++) {

			Tmpl8::Pixel colorSrc = copy->GetBuffer()[frame * (copy->GetHeight()) + x + y * copy->GetPitch()];
			Tmpl8::Pixel colorDst = screen->GetBuffer()[X + x + (y + Y) * screen->GetPitch()];
			//get the alpha of the source
			unsigned char Asrc = ((colorSrc & 0xFF000000) >> 24) / 255.0f * alpha;
			//channels of the source
			unsigned char Rsrc = (colorSrc & Tmpl8::RedMask) >> 16;
			unsigned char Gsrc = (colorSrc & Tmpl8::GreenMask) >> 8;
			unsigned char Bsrc = (colorSrc & Tmpl8::BlueMask);

			//channels of the destination
			unsigned char Rdst = (colorDst & Tmpl8::RedMask) >> 16;
			unsigned char Gdst = (colorDst & Tmpl8::GreenMask) >> 8;
			unsigned char Bdst = (colorDst & Tmpl8::BlueMask);
			//alpha sub-blending
			Rdst = static_cast<unsigned char>(R * Asrc + (1 - Asrc) * Rdst);
			Gdst = static_cast<unsigned char>(G * Asrc + (1 - Asrc) * Gdst);
			Bdst = static_cast<unsigned char>(B * Asrc + (1 - Asrc) * Bdst);
			
			
			Tmpl8::Pixel c = Rdst << 16 | Gdst << 8 | Bdst;

			screen->GetBuffer()[X + x + (y + Y) * screen->GetPitch()] = c;
		}
	}
}
