#pragma once
struct RotationVar
{
	const float ANGLE_SIZE;
	const float OFFSET_SPRITE;
	const float SPRITE_OFFSET;

	explicit RotationVar(const float angleSize = 360 / 32.0f, const float offsetSprite = 90.0f,
		const float spriteOffset = 33)
		: ANGLE_SIZE(angleSize),
		OFFSET_SPRITE(offsetSprite),
		SPRITE_OFFSET(spriteOffset)
	{
	}
};
