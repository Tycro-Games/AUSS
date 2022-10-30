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
	ParallaxProp(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, float speed = 1.0f);
	~ParallaxProp();

	// Inherited via Entity
	virtual void Update(float deltaTime) override;

	virtual void Render(Tmpl8::Surface* screen) override;
	Moveable* getMover() const;
private:
	MoveInstance* move;



};

