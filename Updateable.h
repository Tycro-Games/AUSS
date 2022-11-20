#pragma once
class Updateable {
public:
	Updateable() {  }
	virtual ~Updateable() {}
	virtual void Update(float deltaTime) = 0;


	inline bool getUpdateable() const { return isUpdateable; }
	inline void setUpdateable(bool val) { isUpdateable = val; }
protected:
	bool isUpdateable = true;
};
