#include "FadeInOut.h"

FadeInOut::FadeInOut(const Event& ev) :
	sp(new Tmpl8::Surface(spritePath.string().c_str()), 1),
	toCall(ev)
{
	currenT = 0;
}

void FadeInOut::FadeIn()
{
	

}

void FadeInOut::FadeOut()
{
	toCall();
}

void FadeInOut::Draw(Tmpl8::Surface* screen)
{
	spriteTransparency.SetTransperency(&sp, screen, 0, 0, linerF, 1);
}

void FadeInOut::Update(float deltaTime)
{
	fadeOut.Update(deltaTime);
	if (!fadeOut.isFinished) {
		currenT += deltaTime;
		linerF = currenT / FADE_OUT;
	}

}

void FadeInOut::Init()
{
	currenT = 0;
	fadeIn.Init(std::bind(&FadeInOut::FadeIn, this), FADE_IN);

	fadeOut.Init(std::bind(&FadeInOut::FadeOut, this), FADE_OUT);
}
