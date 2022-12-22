#pragma once
#include "Observer.h"

class Score : public Observer
{
public:
	Score() = default;
	~Score() override = default;

	// Inherited via Observer
	void onNotify(int points, EventType event) override;
	void Init();
	unsigned int getTotal() const;

private:
	unsigned int totalScore = 0;
	unsigned int currentScore = 0;
	float multiplier = 1.0f;
};
