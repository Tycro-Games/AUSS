#include "FadingOut.h"
#include <algorithm>
FadingOut::FadingOut(const Event& ev) :
	sp(new Tmpl8::Surface(spritePath.string().c_str()), 1),
	toCall(ev)
{
	currenT = 0;
}



void FadingOut::FadeOut()
{
	toCall();
}

void FadingOut::Draw(Tmpl8::Surface* screen)
{
	spriteTransparency.SetTransperency(&sp, screen, 0, 0, linerF, 0);
}

void FadingOut::Update(float deltaTime)
{
	fadeOut.Update(deltaTime);
	if (!fadeOut.isFinished) {
		currenT += deltaTime;
		linerF = std::clamp(currenT / FADE_OUT, 0.0f, 1.0f);
	}


}

void FadingOut::Init()
{
	currenT = 0;

	fadeOut.Init(std::bind(&FadingOut::FadeOut, this), FADE_OUT);
}
