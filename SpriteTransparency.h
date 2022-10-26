#pragma once
#include "surface.h"
class SpriteTransparency
{

public:
	SpriteTransparency(Tmpl8::Surface*);
	~SpriteTransparency();
	void SetTransperency(Tmpl8::Surface* sprit, Tmpl8::Surface* screen, float alpha);





private:
	Tmpl8::Surface* copy = nullptr;
};

