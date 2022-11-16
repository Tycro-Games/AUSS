#include "Timer.h"

Timer::Timer(Callable* entity, float DesiredTime, bool loop) :
	toCall(entity),

	loop(loop)
{
	desiredTime = DesiredTime;
	ResetVar();
}

Timer::Timer()
{
	toCall = nullptr;
}

void Timer::init(Callable* entity, float DesiredTime, bool loop)
{
	ResetVar();
	toCall = entity;
	desiredTime = DesiredTime;
	this->loop = loop;
}

void Timer::ResetVar()
{
	isFinished = false;
	currentTime = 0.0f;
}

Timer::~Timer()
{
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
		toCall->Call();
	}
}
