#pragma once
class Renderable {
public:
	Renderable() {}
	virtual ~Renderable() {}
	virtual void Render(Tmpl8::Surface* screen) = 0;

	bool isRenderable = true;
	void SetRenderable(bool render) { isRenderable = render; }
};