#pragma once
#include "surface.h"
#include "template.h"

#include "Collider.h"
#include "vector.h"
#include <vector>
#include "Renderable.h"
#include "Updateable.h"

#include <iostream>
#include "Obstacle.h"
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

class Tilemap :public Renderable, public Updateable
{
public:
	Tilemap();
	~Tilemap();

	// Inherited via Renderable
	virtual void Render(Tmpl8::Surface* screen) override;


	// Inherited via Updateable
	virtual void Update(float deltaTime) override;

	Tmpl8::vec2* GetPos() {
		return &pos;
	}Tmpl8::vec2 GetOffset() {
		return   pos - lastPos;
	}
	void ResetOffset() {
		lastPos = pos;
	}
	Collider* GetCol() {
		return col;
	}Collider GetGameBounds() {
		return Collider(
			Tmpl8::vec2(-OFFSET_X + pos.x + TILE_SIZE, -OFFSET_Y + pos.y + TILE_SIZE),
			Tmpl8::vec2(OFFSET_X + pos.x - TILE_SIZE, OFFSET_Y + pos.y - TILE_SIZE));
	}
	bool IsFree(float x, float y) {
		Tmpl8::vec2 targetPos = Tmpl8::vec2(x, y);
		x += OFFSET_X - (pos.x);
		y += OFFSET_Y - (pos.y);
		int tx = static_cast<int>(x / TILE_SIZE), ty = static_cast<int>(y / TILE_SIZE);
		//verifies if the position is actually colliding with the obstacle
		if (tiles[tx + ty * X_TILES].IsBlocking &&
			Collider::Contains(*tiles[tx + ty * X_TILES].obs->getColl(), targetPos))
			return false;
		return true;
	}

	bool IsFree(float x, float y, Collider& col) {
		Tmpl8::vec2 targetPos = Tmpl8::vec2(x, y);
		x += OFFSET_X - (pos.x);
		y += OFFSET_Y - (pos.y);
		size_t tx = static_cast<size_t>(x / TILE_SIZE), ty = static_cast<size_t>(y / TILE_SIZE);
		//verifies if the position is actually colliding with the obstacle
		if (tiles[tx + ty * X_TILES].IsBlocking &&
			Collider::Contains(*tiles[tx + ty * X_TILES].obs->getColl(), targetPos)) {
			col = *tiles[tx + ty * X_TILES].obs->getColl();
			return false;
		}
		return true;
	}
	Obstacle* GetObstacle(float x, float y) const {
		x += OFFSET_X - (pos.x);
		y += OFFSET_Y - (pos.y);
		size_t tx = static_cast<size_t>(x / TILE_SIZE), ty = static_cast<size_t>(y / TILE_SIZE);

		return tiles[tx + ty * X_TILES].obs;
	}
	void SetPos(const Tmpl8::vec2 p) {
		pos = p;
	}
private:
	void DrawTile(Tmpl8::Surface* screen, int tx, int ty, int x, int y);
	Tmpl8::vec2 pos;
	Tmpl8::vec2 lastPos;
	Tmpl8::Surface tileSurface;

	//consts
	// edges
	//top tile edge, shorter names for readbility
	const Tile TEL = { false, 864, 72, 72,72 };
	const Tile TEM = { false, 936, 72, 72,72 };
	const Tile TER = { false, 1008, 72, 72,72 };
	//side tile edge
	const Tile SET = { false, 720, 0, 72,72 };
	const Tile SEM = { false, 720, 72, 72,72 };
	const Tile SEB = { false, 720, 144, 72,72 };
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
	const Tile OMM = { false, 504, 72, 72,72 };//mid part
	const Tile OMR = { true, 576, 72, 72,72 ,0 , 0, 25, 0 };

	const Tile OLB = { true, 432, 144, 72,72, 23, 0, 23, 24 };
	const Tile OMB = { true, 504, 144, 72,72 ,0 , 0, 0, 24 };
	const Tile ORB = { true, 576, 144, 72,72 , 0, 0, 25, 24 };

	static const uint32_t X_TILES = 24;
	static const uint32_t Y_TILES = 16;

	const int TILE_SIZE = 72;
	const int TILEMAP_SIZE = 1940;
	//center the tilemap
	const int OFFSET_X = TILE_SIZE * X_TILES / 2;
	const int OFFSET_Y = TILE_SIZE * Y_TILES / 2;

	Collider* col;
	vector<Obstacle*> blockingTiles;

	Tile tiles[X_TILES * Y_TILES] = {
	  CLT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CMT,CRT,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,OLT,OMT,ORT,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,OLM,OMM,OMR,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,OLB,OMB,ORB,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,OLT,OMT,ORT,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,OLM,OMM,OMR,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,OLB,OMB,ORB,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CRM,
	  CLB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CMB,CRB,


	};


};