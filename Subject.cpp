#include "Subject.h"

void Subject::addObserver(Observer* obs)
{
	observers.push_back(obs);
}

void Subject::removeObserver(Observer* obs)
{
	observers.remove(obs);
}

void Subject::notify(int points, PointTypes event)
{
	for (int i = 0; i < observers.getCount(); i++) {
		observers[i]->onNotify(points, event);
	}
}
