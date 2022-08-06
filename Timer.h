#pragma once
#include "Updateable.h"
#include "Callable.h"
class Timer :public Updateable {
	// Inherited via Updateable
public:
	Timer(Callable* entity, float DesiredTime, bool loop = false);
	Timer();
	void Init(Callable* entity, float DesiredTime, bool loop = false);
	void ResetVar();
	virtual ~Timer();
	virtual void Update(float deltaTime) override;
	bool isFinished = false;
private:
	float currentTime = 0.0f;
	float desiredTime = 1.0f;
	bool loop = false;

	Callable* toCall;
};
