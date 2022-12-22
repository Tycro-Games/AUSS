#pragma once
#include "template.h"
#include "Renderable.h"
class ShieldLine final :public Renderable
{
public:
	ShieldLine() = default;
	~ShieldLine() override = default;
	void UpdateLine(const Tmpl8::vec2& midPoint, float angle, float size);
	void CheckCollisionProjectiles() const;
	void Render(Tmpl8::Surface* screen) override;
private:
	Tmpl8::vec2 v0, v1;
	const int COLOR = 0xFF00FF;

};

