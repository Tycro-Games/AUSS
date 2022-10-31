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

			Tmpl8::Pixel colorSrc = sprit->GetBuffer()[frame * (copy->GetHeight()) + x + y * sprit->GetPitch()];
			Tmpl8::Pixel colorDst = screen->GetBuffer()[X + x + (y + Y) * screen->GetPitch()];
			//get the alpha of the source
			unsigned char Asrc = ((colorSrc >> 24) / 255.0f * alpha;
			//channels of the source
			unsigned char Rsrc = static_cast<unsigned char>(colorSrc >> 16);
			unsigned char Gsrc = static_cast<unsigned char>(colorSrc >> 8);
			unsigned char Bsrc = static_cast<unsigned char>(colorSrc);

			//channels of the destination
			unsigned char Rdst = static_cast<unsigned char>(colorDst >> 16);
			unsigned char Gdst = static_cast<unsigned char>(colorDst >> 8);
			unsigned char Bdst = static_cast<unsigned char>(colorDst);
			//alpha sub-blending
			Rdst = static_cast<unsigned char>(static_cast<float>(Rsrc) * Asrc + (1 - Asrc) * static_cast<float>(Rdst));
			Gdst = static_cast<unsigned char>(static_cast<float>(Gsrc) * Asrc + (1 - Asrc) * static_cast<float>(Gdst));
			Bdst = static_cast<unsigned char>(static_cast<float>(Bsrc) * Asrc + (1 - Asrc) * static_cast<float>(Bdst));
			

			Tmpl8::Pixel c = Rdst << 16 | Gdst << 8 | Bdst;

			screen->GetBuffer()[X + x + (y + Y) * screen->GetPitch()] = c;
		}
	}
}
