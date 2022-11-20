#pragma once
#include "surface.h"
class Renderable {
public:
	Renderable() {}
	virtual ~Renderable() {}
	virtual void Render(Tmpl8::Surface* screen) = 0;

	inline bool getRenderable()const { return isRenderable; }
	inline bool setRenderable(bool val) { isRenderable = val; }
protected:
	bool isRenderable = true;
};