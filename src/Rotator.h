#pragma once
#include "MoveToADirection.h"


class Rotator
{
public:
	Rotator(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection*);
	Rotator();
	void Init(Tmpl8::vec2* pos, Tmpl8::vec2* dir, RotationVar* rVar, unsigned int* frame, MoveToADirection*);
	void Init(Tmpl8::vec2* pos, Tmpl8::vec2* dir, MoveToADirection*);
	void RotateToDirection(const Tmpl8::vec2&);
	void Reflect(Tmpl8::vec2 normal);
	~Rotator() {};
protected:
	unsigned int* frame;
	Tmpl8::vec2* pos;
	Tmpl8::vec2* dir;
	RotationVar* rVar;
	MoveToADirection* mover;

};

