#include "SpriteTransparency.h"

SpriteTransparency::SpriteTransparency(Tmpl8::Surface* sprite)
	: copy(new Tmpl8::Surface(sprite->GetPitch(), sprite->GetHeight()))
{
	sprite->CopyTo(copy, 0, 0);
}

SpriteTransparency::~SpriteTransparency()
{
	delete copy;
}

void SpriteTransparency::SetTransperency(Tmpl8::Sprite* sprit, Tmpl8::Surface* screen, int X, int Y, float alpha, unsigned int frame)
{
	for (int x = 0; x < sprit->GetWidth(); x++) {
		for (int y = 0; y < sprit->GetHeight(); y++) {

			Tmpl8::Pixel copyPixel = copy->GetBuffer()[frame * (copy->GetHeight()) + x + y * copy->GetPitch()];

			unsigned char A = (copyPixel & 0xFF000000) >> 24;
			unsigned char R = (copyPixel & Tmpl8::RedMask) >> 16;
			unsigned char G = (copyPixel & Tmpl8::GreenMask) >> 8;
			unsigned char B = (copyPixel & Tmpl8::BlueMask);

			Tmpl8::Pixel pixe = screen->GetBuffer()[X + x + (y + Y) * screen->GetPitch()];

			unsigned char Rdst = (pixe & Tmpl8::RedMask) >> 16;
			unsigned char Gdst = (pixe & Tmpl8::GreenMask) >> 8;
			unsigned char Bdst = (pixe & Tmpl8::BlueMask);
			if (A > 0) {
				R = R * alpha + (1 - alpha) * Rdst;
				G = G * alpha + (1 - alpha) * Gdst;
				B = B * alpha + (1 - alpha) * Bdst;
			}

			Tmpl8::Pixel c = R << 16 | G << 8 | B;

			sprit->GetBuffer()[frame * sprit->GetWidth() + x + y * sprit->GetSurface()->GetPitch()] = c;
		}
	}
}
