#pragma once
#include "MoveToADirection.h"


class Rotator
{
public:
	Rotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar rVar, int* frame, MoveToADirection*);

	void RotateToDirection(Tmpl8::vec2);
	void Reflect(Tmpl8::vec2 normal);
	~Rotator() {};
protected:
	int* frame;
	Tmpl8::vec2* pos;
	Tmpl8::vec2* dir;
	RotationVar rVar;
	MoveToADirection* mover;

};

