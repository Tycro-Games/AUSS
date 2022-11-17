#pragma once
#include "template.h"
struct PosDir
{
	PosDir(Tmpl8::vec2 pos, Tmpl8::vec2 dir) :
		pos(pos),
		dir(dir)
	{

	}

	PosDir() :
		pos(Tmpl8::vec2(0)),
		dir(Tmpl8::vec2(0))
	{

	}
	Tmpl8::vec2 pos, dir;
};