#pragma once
#include "Updateable.h"
#include "Callable.h"
class Timer :public Updateable {
	// Inherited via Updateable
public:
	Timer(Callable* entity, float DesiredTime, bool loop = false);
	virtual ~Timer();
	virtual void Update(float deltaTime) override;
private:
	float currentTime = 0.0f;
	float desiredTime = 1.0f;
	bool loop = false;
	bool isFinished = false;
	Callable* toCall;
};
