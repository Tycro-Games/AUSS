#pragma once
#include "Updateable.h"
class Spawner :public Updateable {
public:
	Spawner(float FireRate = 1.0f);
	~Spawner();

	void setFire(bool fire);
	virtual void Update(float deltaTime) override;
private:
	float fireRate = 1.0f, currentTime, desiredTime;
	// Inherited via Updateable


	bool isSpawning = false;
};