#include "Collider.h"
#include "game.h"
Collider::Collider(Tmpl8::vec2 min, Tmpl8::vec2 max) :
	min(min),
	max(max),
	pos(0),
	collision()
{
}

Collider::Collider(Tmpl8::vec2 min, Tmpl8::vec2 max, Tmpl8::vec2* pos) :
	min(min),
	max(max),
	collision(),
	pos(pos)
{
}

Collider::Collider() :
	min(0),
	max(0),
	collision(),
	pos(0)
{
}
//checks with the current pos
bool Collider::InGameBounds(Collider& col) {
	return col.Collides(Tmpl8::Game::tileMap->GetGameBounds());
}
//checks with the position parameter
bool Collider::InGameBounds(Tmpl8::vec2& pos, Collider& col)
{
	return Overlaps(col.At(pos), Tmpl8::Game::tileMap->GetGameBounds());

}

Tmpl8::vec2 Collider::GetNormalEdgeScreen(const Tmpl8::vec2& pos, const Collider& col)
{
	Tmpl8::vec2 normal;
	Collider gameBounds = Tmpl8::Game::tileMap->GetGameBounds();
	if (pos.x + col.min.x < gameBounds.min.x || pos.x + col.max.x > gameBounds.max.x)
		normal = Tmpl8::vec2(1, 0);
	else//if (pos.y + col.min.y < gameBounds.min.y || pos.y + col.max.y < gameBounds.max.y)
		normal = Tmpl8::vec2(0, 1);
	return normal;
}

Collider::~Collider()
{
}


