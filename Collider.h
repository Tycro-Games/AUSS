#pragma once
#include "template.h"
struct Collider
{
public:
	Collider(Tmpl8::vec2 min, Tmpl8::vec2 max);
	~Collider();
	Tmpl8::vec2 min, max;

};


