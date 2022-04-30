#pragma once
class Renderable {
public:
	Renderable() {}
	virtual ~Renderable() {}
	virtual void Render(Tmpl8::Surface* screen) = 0;
};