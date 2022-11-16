#pragma once
#include "surface.h"
class Renderable {
public:
	Renderable() {}
	virtual ~Renderable() {}
	virtual void Render(Tmpl8::Surface* screen) = 0;

	bool isRenderable = true;
	inline bool getRenderable() { return isRenderable; }

};