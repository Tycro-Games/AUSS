#include "Timer.h"

Timer::Timer(Callable* entity, float DesiredTime, bool loop) :
	toCall(entity),
	desiredTime(DesiredTime),
	loop(loop)
{
	isFinished = false;
}

Timer::Timer()
{
	toCall = nullptr;
}

void Timer::Init(Callable* entity, float DesiredTime, bool loop)
{
	isFinished = false;
	currentTime = 0.0f;
	toCall = entity;
	desiredTime = DesiredTime;
	this->loop = loop;
}

Timer::~Timer()
{
}

void Timer::Update(float deltaTime)
{
	if (isFinished)
		return;
	if (currentTime < desiredTime)
		currentTime += deltaTime;
	else {

		if (loop)
			currentTime = 0;
		else
			isFinished = true;
		toCall->Call();
	}
}
