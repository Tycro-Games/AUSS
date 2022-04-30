#pragma once
class Updateable {
public:
	Updateable() {}
	virtual ~Updateable() {}
	virtual void Update(float deltaTime) = 0;
};
