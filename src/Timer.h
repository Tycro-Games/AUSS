#pragma once
#include "Updateable.h"

#include <functional>
using Event = std::function<void()>;

class Timer final : public Updateable
{
	// Inherited via Updateable
public:
	Timer(Event evt, float _desiredTime, bool loop = false);
	Timer();
	void Init(const Event& evt, float _desiredTime, bool _loop = false);
	void ResetVar();
	~Timer() override = default;
	void Update(float deltaTime) override;
	bool isFinished = false;
	bool FinishedLoop() const { return currentTime == 0; }

private:
	float currentTime = 0.0f;
	float desiredTime = 1.0f;
	bool loop = false;

	Event toCall;
};
