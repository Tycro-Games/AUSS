#include "Timer.h"

Timer::Timer(Event evt, const float _desiredTime, const bool loop) :
	loop(loop),
	toCall(std::move(evt))
{
	desiredTime = _desiredTime;
	ResetVar();
}

Timer::Timer()
{
	toCall = nullptr;
}

void Timer::Init(const Event& evt, const float _desiredTime, const bool _loop)
{
	ResetVar();
	toCall = evt;
	desiredTime = _desiredTime;
	this->loop = _loop;
}

void Timer::ResetVar()
{
	isFinished = false;
	currentTime = 0.0f;
}



void Timer::Update(const float deltaTime)
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
