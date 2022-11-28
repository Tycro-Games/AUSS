#pragma once
#include "Updateable.h"

#include <functional>
using Event = std::function<void()>;

class Timer :public Updateable {
	// Inherited via Updateable
public:
	Timer(const Event& entity, float DesiredTime, bool loop = false);
	Timer();
	void Init(const Event& entity, float DesiredTime, bool loop = false);
	void ResetVar();
	~Timer() = default;
	void Update(float deltaTime) override;
	bool isFinished = false;
	bool FinishedLoop() { return currentTime == 0; };
private:
	float currentTime = 0.0f;
	float desiredTime = 1.0f;
	bool loop = false;

	Event toCall;

};
