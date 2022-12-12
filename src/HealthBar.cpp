#include "HealthBar.h"
#include "MathFunctions.h"
using namespace Tmpl8;
HealthBar::HealthBar() :
	bar(new Surface(barPath.string().c_str()), 1),
	decoration(new Surface(decorationPath.string().c_str()), 1)
{
	Init();
}

void HealthBar::Init()
{
	linearF = 1;
}

void HealthBar::Draw(Tmpl8::Surface* screen)
{
	int x = static_cast<int>(position.x);
	int y = static_cast<int>(position.y);
	decoration.Draw(screen, x, y);
	clipSprite.DrawSprite(screen, *bar.GetSurface(), linearF, x + SPRITE_OFFSETX, y);
}

void HealthBar::onNotify(int points, EventType eventt)
{
	switch (eventt)
	{
	case EventType::PlayerTakesDamage:
		//minimum and max health of the player
		linearF = MathFunctions::InverseLerp(0.0f, 100.0f, static_cast<float>(points));
		break;
	default:
		break;
	}
}
