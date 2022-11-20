#pragma once
#include "Observer.h"
class Score : public Observer
{
public:
	Score();
	~Score();

	// Inherited via Observer
	void onNotify(int points, PointTypes event) override;
	void Init();
	unsigned int getTotal();
private:
	unsigned int totalScore = 0;
	unsigned int currentScore = 0;
	float multiplier = 1.0f;





};


