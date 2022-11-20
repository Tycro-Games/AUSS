#pragma once
#include "Entity.h"
#include "MoveInstance.h"
class ParallaxProp : public Entity
{
public:
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="sprite"></param>
	/// <param name="pos"></param>
	/// <param name="speed">speed of the parallax</param>
	ParallaxProp(const std::filesystem::path& spritePath, float speed = 1.0f);
	~ParallaxProp();
	void Init(const Tmpl8::vec2 pos, float speed = 1.0f);
	// Inherited via Entity
	void Update(float deltaTime) override;

	void Render(Tmpl8::Surface* screen) override;
	Moveable* getMover();
private:
	MoveInstance moveInstance;



};

