#pragma once
#include "template.h"
#include "Renderable.h"
class ShieldLine :public Renderable
{
public:
	ShieldLine() = default;
	~ShieldLine() = default;
	void UpdateLine(const Tmpl8::vec2& midPoint, const float angle,const float size);
	void CheckCollisionProjectiles();
	void Render(Tmpl8::Surface* screen) override;
private:
	Tmpl8::vec2 v0, v1;
	const int COLOR = 0xFF00FF;

};

