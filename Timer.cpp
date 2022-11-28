#include "Timer.h"

Timer::Timer(const Event& evt, float DesiredTime, bool loop) :
	toCall(evt),

	loop(loop)
{
	desiredTime = DesiredTime;
	ResetVar();
}

Timer::Timer()
{
	toCall = nullptr;
}

void Timer::Init(const Event& evt, float DesiredTime, bool loop)
{
	ResetVar();
	toCall = evt;
	desiredTime = DesiredTime;
	this->loop = loop;
}

void Timer::ResetVar()
{
	isFinished = false;
	currentTime = 0.0f;
}



void Timer::Update(float deltaTime)
{

	if (isFinished || !isUpdateable)
		return;
	if (currentTime < desiredTime)
		currentTime += deltaTime;
	else {

		if (loop)
			currentTime = 0;
		else
			isFinished = true;
		toCall();
	}
}
