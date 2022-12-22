#pragma once
#include "surface.h"
#include "template.h"

#include "Collider.h"
#include "Obstacle.h"
#include "ParallaxProp.h"
#include "Followable.h"
#include <vector>


struct Tile
{
	/// <summary>
	/// is it blocking the player's path?
	/// </summary>
	bool is_blocking;
	/// <summary>
	/// x position on the tilemap
	/// </summary>
	int x = 0;
	/// <summary>
	/// y position on the tilemap
	/// </summary>
	int y = 0;
	/// <summary>
	/// dimensions of the tile on x
	/// </summary>
	unsigned int xd = 0;
	/// <summary>
	/// dimension of the tile on y
	/// </summary>
	unsigned int yd = 0;
	/// <summary>
	/// Offset for the collider obstacle
	/// </summary>
	float pivotX = 0;
	/// <summary>
	/// Offset for the collider obstacle
	/// </summary>
	float pivotY = 0;
	/// <summary>
	/// Offset for the collider obstacle
	/// </summary>
	float dimensionsX = 0;
	/// <summary>
	/// Offset for the collider obstacle
	/// </summary>
	float dimensionsY = 0;

	Obstacle* obs = nullptr;
};

class Tilemap final : public Renderable, public Updateable, public Followable
	// NOLINT(cppcoreguidelines-special-member-functions)
{
public:
	/**
	 * \brief The initialization method of the tilemap.
	 * \param _pos The position that the tilemap will be set to.
	 */
	void Init(const Tmpl8::vec2& _pos);
	Tilemap();
	~Tilemap() override;
	// Inherited via Renderable
	void Render(Tmpl8::Surface* screen) override;
	// Inherited via Updateable
	void Update(float deltaTime) override;
	//Inherited via Followable
	void ResetOffset() override;
	/**
	 * \brief Getter for the collider of the tilemap.
	 * \return The collider of the tilemap.
	 */
	Collider& GetCollider();

	/**
	 * \brief Returns the playable area.
	 * \return The bounds of the game area as a collider.
	 */
	inline Collider GetGameBounds() const;
	/**
	 * \brief	Checks if the tile at position (x,y) is free.
	 * \param x coordonate of the vector.
	 * \param y coordonate of the vector.
	 * \return A boolean.
	 */
	bool IsFreeTile(float x, float y) const;
	/**
	 * \brief Check if the collider is not touching any obstacle with any of its corners.
	 * \param _pos Position of the object to be checked.
	 * \param collider Collider of the object to be checked.
	 * \return A boolean
	 */
	bool IsFreeTile(const Tmpl8::vec2& _pos, const Collider& collider) const;

	/**
	 * \brief Gets the obstacle at the (x,y) position.
	 * \param x X coordonate of the position of the obstacle.
	 * \param y Y coordonate of the position of the obstacle.
	 * \return A const pointer to the obstacle.
	 */
	const Obstacle* GetObstacle(float x, float y) const;


	Tmpl8::vec2* GetPos();
	const Tmpl8::vec2 getOffset() override;

private:
	const Obstacle* GetObstacle(size_t x, size_t y) const;

	//returns the collider at the coordinates x and y in the col variable
	bool IsFreeTile(float x, float y, Collider& obsCollider) const;
	void ClearObstacles();
	/**
	 * \brief Draws a tile with clipping from the position of the source to the destination.
	 * \param screen Surface to be drawn to.
	 * \param tx X coordonate of the tilemap source.
	 * \param ty Y cooordonate of the tilemap source.
	 * \param x X coordonate of the destination position
	 * \param y Y coordonate fo the destination position.
	 */
	void DrawTile(Tmpl8::Surface* screen, int tx, int ty, int x, int y);

	Tmpl8::vec2 pos;
	Tmpl8::Surface tileSurface;
	ParallaxProp prop;
	//consts
	const Tile BLK = { false };
	const Tile OOO = { false, 504, 72, 72, 72 }; //outer part

	//corners L=Left R=Right T=Top B=Bottom M=Mid
	//top 
	const Tile CLT = { false, 0, 0, 72, 72 };
	const Tile CMT = { false, 72, 0, 72, 72 };
	const Tile CRT = { false, 144, 0, 72, 72 };
	//mid
	const Tile CLM = { false, 0, 72, 72, 72 };
	const Tile CMM = { false, 74, 72, 72, 72 };
	const Tile CRM = { false, 144, 72, 72, 72 };
	//bottom
	const Tile CLB = { false, 0, 144, 72, 72 };
	const Tile CMB = { false, 74, 144, 72, 72 };
	const Tile CRB = { false, 144, 144, 72, 72 };

	//obstacle
	const Tile OLT = { true, 432, 0, 72, 72, 23, 24, 23, 24 };
	const Tile OMT = { true, 504, 0, 72, 72, 0, 24, 0, 24 };
	const Tile ORT = { true, 576, 0, 72, 72, 0, 24, 25, 24 };

	const Tile OLM = { true, 432, 72, 72, 72, 23, 0, 25, 0 };
	const Tile OMM = { true, 504, 72, 72, 72 }; //mid part
	const Tile OMR = { true, 576, 72, 72, 72, 0, 0, 25, 0 };

	const Tile OLB = { true, 432, 144, 72, 72, 23, 0, 23, 24 };
	const Tile OMB = { true, 504, 144, 72, 72, 0, 0, 0, 24 };
	const Tile ORB = { true, 576, 144, 72, 72, 0, 0, 25, 24 };

	static constexpr int X_TILES = 24;
	static constexpr int Y_TILES = 16;

	const int TILE_SIZE = 72;
	const int EDGE_SIZE = TILE_SIZE * 3; //three tiles from the edge
	//center the tilemap so the entire map is two screens
	const int OFFSET_X = TILE_SIZE * X_TILES / 2;
	const int OFFSET_Y = TILE_SIZE * Y_TILES / 2;

	Collider col;
	std::vector<Obstacle*> blockingTiles;

	Tile tiles[X_TILES * Y_TILES] = {
		OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO,
		OOO, OOO,
		OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO,
		OOO, OOO,
		OOO, OOO, CLT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CMT, CRT,
		OOO, OOO,
		OOO, OOO, CLM, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, CRM,
		OOO, OOO,
		OOO, OOO, CLM, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, CRM,
		OOO, OOO,
		OOO, OOO, CLM, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, OLT, OMT, ORT, BLK, BLK, BLK, BLK, BLK, CRM,
		OOO, OOO,
		OOO, OOO, CLM, BLK, BLK, BLK, OLT, ORT, BLK, BLK, BLK, BLK, BLK, OLB, OMB, ORB, BLK, BLK, BLK, BLK, BLK, CRM,
		OOO, OOO,
		OOO, OOO, CLM, BLK, BLK, BLK, OLB, ORB, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, CRM,
		OOO, OOO,
		OOO, OOO, CLM, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, CRM,
		OOO, OOO,
		OOO, OOO, CLM, BLK, BLK, BLK, BLK, BLK, BLK, OLT, ORT, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, CRM,
		OOO, OOO,
		OOO, OOO, CLM, BLK, OLT, ORT, BLK, BLK, BLK, OLB, ORB, BLK, BLK, BLK, BLK, BLK, BLK, OLT, OMT, ORT, BLK, CRM,
		OOO, OOO,
		OOO, OOO, CLM, BLK, OLB, ORB, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, OLB, OMB, ORB, BLK, CRM,
		OOO, OOO,
		OOO, OOO, CLM, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, CRM,
		OOO, OOO,
		OOO, OOO, CLB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CMB, CRB,
		OOO, OOO,
		OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO,
		OOO, OOO,
		OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO,
		OOO, OOO
	};
};

inline void Tilemap::ResetOffset()
{
	lastPos = pos;
}

inline Collider& Tilemap::GetCollider()
{
	return col;
}

inline Tmpl8::vec2* Tilemap::GetPos()
{
	return &pos;
}

inline const Tmpl8::vec2 Tilemap::getOffset()
{
	return pos - lastPos;
}

inline Collider Tilemap::GetGameBounds() const
{
	return {
		Tmpl8::vec2(pos.x + static_cast<float>(-OFFSET_X + EDGE_SIZE),
					pos.y + static_cast<float>(-OFFSET_Y + EDGE_SIZE)),
		Tmpl8::vec2(pos.x + static_cast<float>(OFFSET_X - EDGE_SIZE), pos.y + static_cast<float>(OFFSET_Y - EDGE_SIZE))
	};
}
