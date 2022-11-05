#pragma once
//based on https://gameprogrammingpatterns.com/observer.html
enum PointTypes
{
	Additive,
	Multiplicative,
	Total

};
class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(int points, PointTypes event) = 0;
};
