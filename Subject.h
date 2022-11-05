#pragma once
//also based on https://gameprogrammingpatterns.com/observer.html
#include "vector.h"
#include "Observer.h"
class Subject
{
public:
	void addObserver(Observer* obs);
	void removeObserver(Observer* obs);
protected:
	void notify(int points, PointTypes event);
private:
	vector<Observer*> observers;
};

