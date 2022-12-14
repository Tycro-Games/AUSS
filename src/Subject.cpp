#include "Subject.h"
using namespace std;
void Subject::addObserver(Observer* obs)
{
	observers.push_back(obs);
}

void Subject::removeObserver(Observer* obs)
{
	observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
}

void Subject::notify(const int points, const EventType event)
{
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->onNotify(points, event);
	}
}
