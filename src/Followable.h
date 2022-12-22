#pragma once
#include "template.h"

class Followable
{
public:
	Followable() = default;


	virtual ~Followable() = default;

protected:
	virtual const Tmpl8::vec2 getOffset() = 0;
	virtual void ResetOffset() = 0;
	Tmpl8::vec2 lastPos;
};
