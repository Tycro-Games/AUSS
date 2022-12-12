#pragma once
//based on https://gameprogrammingpatterns.com/observer.html
enum class EventType
{
	EnemyDeath,
	BonusConditions,
	EndOfAWave,
	PlayerTakesDamage

};
class Observer
{
public:
	virtual ~Observer() = default;
	virtual void onNotify(int points, EventType eventt) = 0;
};
