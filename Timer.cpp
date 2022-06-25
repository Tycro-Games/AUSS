#include "Timer.h"

Timer::Timer(Callable* entity, float DesiredTime, bool loop) :
	toCall(entity),
	desiredTime(DesiredTime),
	loop(loop)
{

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
