#pragma once
#include "Moveable.h"
class MoveInstance :public Moveable
{
public:
	MoveInstance(Tmpl8::vec2*);
	~MoveInstance();

private:


	// Inherited via Moveable
	virtual void Update(float deltaTime) override;

};




