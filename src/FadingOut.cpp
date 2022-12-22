#include "FadingOut.h"
#include <algorithm>

#include "SpriteTransparency.h"

FadingOut::FadingOut(Event ev) :
	sp(new Tmpl8::Surface(spritePath.string().c_str()), 1),
	toCall(std::move(ev))
{
	currenT = 0;
}


void FadingOut::FadeOut() const
{
	toCall();
}

void FadingOut::Draw(Tmpl8::Surface* screen)
{
	SpriteTransparency::SetTransparency(&sp, screen, 0, 0, linerF, 0);
}

void FadingOut::Update(const float deltaTime)
{
	fadeOut.Update(deltaTime);
	if (!fadeOut.isFinished)
	{
		currenT += deltaTime;
		linerF = std::clamp(currenT / FADE_OUT, 0.0f, 1.0f);
	}
}

void FadingOut::Init()
{
	currenT = 0;

	fadeOut.Init(std::bind(&FadingOut::FadeOut, this), FADE_OUT);
}
