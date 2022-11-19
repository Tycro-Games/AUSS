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
	bool IsBlocking;
	/// <summary>
	/// x position on the tilemap
	/// </summary>
	int x;
	/// <summary>
	/// y position on the tilemap
	/// </summary>
	int y;
	/// <summary>
	/// dimensions of the tile on x
	/// </summary>
	unsigned int xd;
	/// <summary>
	/// dimension of the tile on y
	/// </summary>
	unsigned int yd;
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

class Tilemap :public Renderable, public Updateable, public Followable
{
public:
	void Init(const Tmpl8::vec2& _pos);
	Tilemap();
	~Tilemap();

	// Inherited via Renderable
	virtual void Render(Tmpl8::Surface* screen) override;


	// Inherited via Updateable
	virtual void Update(float deltaTime) override;
	//Inherited via Followable
	virtual void ResetOffset() override {
		lastPos = pos;
	}

	inline Collider& GetCol() {
		return col;
	}
	/// <summary>
	/// The bounds where an object is inside the map
	/// </summary>
	/// <returns></returns>
	inline Collider GetGameBounds() const;

	bool IsFree(float x, float y) const;
	//returns the collider at the coordonates x and y in the col variable
	bool IsFree(float x, float y, Collider& col) const;

	const Obstacle* GetObstacle(float x, float y) const;

	const Obstacle* GetObstacle(size_t x, size_t  y) const;


	void SetPos(const Tmpl8::vec2 p);

	Tmpl8::vec2* GetPos();
	virtual const Tmpl8::vec2 GetOffset() override;

private:
	void DrawTile(Tmpl8::Surface* screen, int tx, int ty, int x, int y);
	Tmpl8::vec2 pos;
	Tmpl8::Surface tileSurface;
	ParallaxProp prop;
	//consts
	const Tile BLK = { false };
	//corners L=Left R=Right T=Top B=Bottom M=Mid
	//top 
	const Tile CLT = { false, 0, 0, 72,72 };
	const Tile CMT = { false, 72, 0, 72,72 };
	const Tile CRT = { false, 144, 0, 72,72 };
	//mid
	const Tile CLM = { false, 0, 72, 72,72 };
	const Tile CMM = { false, 74, 72, 72,72 };
	const Tile CRM = { false, 144, 72, 72,72 };
	//bottom
	const Tile CLB = { false, 0, 144, 72,72 };
	const Tile CMB = { false, 74, 144, 72,72 };
	const Tile CRB = { false, 144, 144, 72,72 };

	//obstacle
	const Tile OLT = { true, 432, 0, 72, 72, 23, 24, 23, 24 };
	const Tile OMT = { true, 504, 0, 72, 72 ,0, 24, 0, 24 };
	const Tile ORT = { true, 576, 0, 72, 72 ,0, 24, 25, 24 };

	const Tile OLM = { true, 432, 72, 72,72, 23, 0, 25, 0 };
	const Tile OMM = { true, 504, 72, 72,72 };//mid part
	const Tile OMR = { true, 576, 72, 72,72 ,0 , 0, 25, 0 };

	const Tile OLB = { true, 432, 144, 72,72, 23, 0, 23, 24 };
	const Tile OMB = { true, 504, 144, 72,72 ,0 , 0, 0, 24 };
	const Tile ORB = { true, 576, 144, 72,72 , 0, 0, 25, 24 };

	static const int X_TILES = 24;
	static const int Y_TILES = 16;

	const int TILE_SIZE = 72;
	const int TILEMAP_SIZE = 1940;
	//center the tilemap so the entire map is two screens
	const int OFFSET_X = TILE_SIZE * X_TILES / 2;
	const int OFFSET_Y = TILE_SIZE * Y_TILES / 2;

	Collider col;
	std::vector<Obstacle*> blockingTiles;

	Tile tiles[X_TILES * Y_TILES] = {
	  CLT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CRT,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,OLT,OMT,ORT,BLK,OLT,OMT,OMT,ORT,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,OLM,OMM,OMR,BLK,OLM,OMM,OMM,OMR,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,OLM,OMM,OMR,BLK,OLB,OMB,OMB,ORB,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,OLB,OMB,ORB,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,OLT,OMT,OMT,OMT,ORT,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,OLM,OMM,OMM,OMM,OMR,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,OLB,OMB,OMB,OMB,ORB,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLM,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,BLK,CRM,
	  CLB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CRB,
	};
};

inline Tmpl8::vec2* Tilemap::GetPos() {
	return &pos;
}
inline const Tmpl8::vec2 Tilemap::GetOffset() {
	return   pos - lastPos;
}
inline Collider Tilemap::GetGameBounds() const {
	return Collider(
		Tmpl8::vec2(-OFFSET_X + pos.x + TILE_SIZE, -OFFSET_Y + pos.y + TILE_SIZE),
		Tmpl8::vec2(OFFSET_X + pos.x - TILE_SIZE, OFFSET_Y + pos.y - TILE_SIZE));
}


