#pragma once
#include "template.h"
//interfaces
#include "Updateable.h"
#include "Renderable.h"

#include<filesystem>
class Entity :public Updateable, public Renderable
{
public:
	Entity(const std::filesystem::path& spritePath, unsigned int numberOfFrames, Tmpl8::vec2 pos);
	void SetActive(bool active) {
		isUpdateable = active;
		isRenderable = active;
	}
	Entity(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos = Tmpl8::vec2(0));
	Entity(const std::filesystem::path& spritePath, unsigned int numberOfFrames);
	void Init(Tmpl8::vec2 pos);
	virtual ~Entity();
	Tmpl8::Sprite* sprite;
	Tmpl8::vec2 pos;

protected:
	unsigned int frame = 0;



private:




};

