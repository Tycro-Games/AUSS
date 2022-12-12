#pragma once
#include "Entity.h"
#include "Collider.h"
class Cursor :public Entity
{
public:
	Cursor(const std::filesystem::path& spritePath, Tmpl8::vec2 pos = Tmpl8::vec2(0));
	void AddOffset();
	~Cursor();
	void Update(float deltaTime) override;
	void ChangePosition(int x, int y);
	void Render(Tmpl8::Surface* screen) override;
	Collider& GetCollider() {
		return col;
	}
private:
	const Tmpl8::vec2 offset = { -13,-13 };
	Collider col;



};

