#pragma once
#include "template.h"
struct PosDir
{
	PosDir(Tmpl8::vec2 pos, Tmpl8::vec2 dir) :
		pos(pos),
		dir(dir)
	{

	}
	Tmpl8::vec2 pos, dir;
};