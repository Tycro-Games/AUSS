#pragma once
class Updateable {
public:
	Updateable() {}
	virtual ~Updateable() {}
	virtual void Update(Tmpl8::Surface* screen) = 0;
};
