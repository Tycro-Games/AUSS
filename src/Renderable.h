#pragma once
#include "surface.h"
class Renderable {
public:
	Renderable() {}
	virtual ~Renderable() {}
	virtual void Render(Tmpl8::Surface* screen) = 0;

	bool getRenderable()const { return isRenderable; }
	void setRenderable(const bool val) { isRenderable = val; }
protected:
	bool isRenderable = true;
};