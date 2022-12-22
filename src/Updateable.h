#pragma once
class Updateable
{
public:
	Updateable() = default;
	virtual ~Updateable() = default;
	virtual void Update(float deltaTime) = 0;


	bool getUpdateable() const { return isUpdateable; }
	void setUpdateable(const bool val) { isUpdateable = val; }

protected:
	bool isUpdateable = true;
};
