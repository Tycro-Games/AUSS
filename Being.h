#pragma once
#include "Entity.h"
#include <filesystem>
class Being : public Entity {
public:
	Being(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, int hp = 100);
	Being();
	Being(const std::filesystem::path& spritePath, unsigned int numberOfFrames, Tmpl8::vec2 pos, int hp = 100);
	void Init(const std::filesystem::path& spritePath, unsigned int numberOfFrames, Tmpl8::vec2 _pos, int _hp = 100);
	virtual ~Being();
	virtual void TakeDamage(int dg);
protected:
	int hp;
	virtual void Die() = 0;



private:
};
