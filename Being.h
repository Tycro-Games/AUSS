#pragma once
#include "Entity.h"
#include <filesystem>
class Being : public Entity {
public:
	Being(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, int hp = 100);
	Being(const std::filesystem::path& spritePath, unsigned int numberOfFrames, Tmpl8::vec2 pos = Tmpl8::vec2(0), int hp = 100);
	void Init(Tmpl8::vec2 _pos, int _hp = 100);
	virtual ~Being() = default;
	virtual void TakeDamage(int dg);
protected:
	int hp;
	virtual void Die() = 0;



private:
};
