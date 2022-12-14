#pragma once
//also based on https://gameprogrammingpatterns.com/observer.html
#include <vector>
#include "Observer.h"
class Subject
{
public:
	void addObserver(Observer* obs);
	void removeObserver(Observer* obs);
protected:
	void notify(int points, EventType event) const;
private:
	std::vector<Observer*> observers;
};

