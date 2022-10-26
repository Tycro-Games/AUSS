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

void SpriteTransparency::SetTransperency(Tmpl8::Surface* sprit, Tmpl8::Surface* screen, float alpha)
{
	for (int x = 0; x < copy->GetPitch(); x++) {
		for (int y = 0; y < copy->GetHeight(); y++) {
			Tmpl8::Pixel pixe = copy->GetBuffer()[x + y * copy->GetPitch()];

			Tmpl8::Pixel R = (pixe & Tmpl8::RedMask) >> 16;
			Tmpl8::Pixel G = (pixe & Tmpl8::GreenMask) >> 8;
			Tmpl8::Pixel B = (pixe & Tmpl8::BlueMask);

			R *= alpha;
			B *= alpha;
			G *= alpha;

			Tmpl8::Pixel c = R << 16 | G << 8 | B;
			sprit->GetBuffer()[x + y * sprit->GetPitch()] = c;
		}
	}
}
