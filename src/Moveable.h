#pragma once

#include "Collider.h"
#include "Updateable.h"
class Moveable :public Updateable
{
public:
	Moveable(Tmpl8::vec2* _pos, Collider* _collider, float _speed = 1.0f);
	explicit Moveable(Tmpl8::vec2* _pos);
	Moveable();
	void Init(Tmpl8::vec2* _pos, Collider* _col, float _speed = 1.0f);
	void Init(Tmpl8::vec2* pos);
	~Moveable() override = default;
	void Update(float deltaTime) override;
	void SetSpeed(float);
	float GetSpeed() const;
	virtual void Translation(Tmpl8::vec2);
	Collider* getColl() const {
		return collider;
	}

protected:
	Tmpl8::vec2* pos;
	Collider* collider;
	float speed;


};



