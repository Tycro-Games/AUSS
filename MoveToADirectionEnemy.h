#pragma once
#include "MoveToADirection.h"
class MoveToADirectionEnemy:public MoveToADirection
{
public:
	MoveToADirectionEnemy(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Collider* col, Callable* call, float speed = 2.0f);
	~MoveToADirectionEnemy();
	virtual void Update(float)override;

private:

};
