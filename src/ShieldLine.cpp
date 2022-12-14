// ReSharper disable CppClangTidyModernizeLoopConvert
#include "ShieldLine.h"

#include <vector>

#include "Collider.h"
#include "game.h"
using namespace std;
using namespace Tmpl8;

void ShieldLine::UpdateLine(const Tmpl8::vec2& midPoint,const float angle,const float size)
{
	v0 = { midPoint.x - cos((angle + 90) * PI / 180) * size,
			midPoint.y - sin((angle + 90) * PI / 180) * size };
	v1 = { midPoint.x + cos((angle + 90) * PI / 180) * size,
		midPoint.y + sin((angle + 90) * PI / 180) * size };
}

void ShieldLine::CheckCollisionProjectiles() const
{
	const std::vector<Collider*> colliders = Game::Get().getColliders();
	Tmpl8::vec2 positionOfIntersection;
	float f_fractionOfIntersection;
	for (size_t i = 0; i < colliders.size(); i++) {
		if (colliders[i]->type == Collider::Type::projectile)
			if (Collider::LineRectangleIntersection(v0, v1, colliders[i]->At(*colliders[i]->pos), positionOfIntersection, f_fractionOfIntersection))
				colliders[i]->toDeactivate = true;
	}
}

void ShieldLine::Render(Tmpl8::Surface* screen)
{
	screen->Line(v0.x, v0.y, v1.x, v1.y, COLOR);

}
