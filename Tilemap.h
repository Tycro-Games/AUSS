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
	int xd;
	/// <summary>
	/// dimension of the tile on y
	/// </summary>
	int yd;

	Obstacle* obs = NULL;
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
		x += OFFSET_X - (pos.x);
		y += OFFSET_Y - (pos.y);
		int tx = static_cast<int>(x / TILE_SIZE), ty = static_cast<int>(y / TILE_SIZE);
		/*std::cout << tx << " " << ty << '\n';*/
		return !tiles[tx + ty * X_TILES].IsBlocking;
	}
	Obstacle* GetObstacle(float x, float y) const {
		x += OFFSET_X - (pos.x);
		y += OFFSET_Y - (pos.y);
		int tx = static_cast<int>(x / TILE_SIZE), ty = static_cast<int>(y / TILE_SIZE);


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
	//bottom
	const Tile CLB = { false, 0, 144, 72,72 };
	//obstacle
	const Tile OLT = { true, 433, 0, 72,72 };
	const Tile OMT = { true, 505, 0, 72,72 };
	const Tile ORT = { true, 577, 0, 72,72 };

	const Tile OLM = { true, 433, 72, 72,72 };
	const Tile OMM = { true, 505, 72, 72,72 };
	const Tile OMR = { true, 577, 72, 72,72 };

	const Tile OLB = { true, 433, 144, 72,72 };
	const Tile OMB = { true, 505, 144, 72,72 };
	const Tile ORB = { true, 577, 144, 72,72 };

	static const uint32_t X_TILES = 24;
	static const uint32_t Y_TILES = 16;
	const int TILE_SIZE = 72;
	const int TILEMAP_SIZE = 1940;
	//center the tilemap
	const int OFFSET_X = TILE_SIZE * X_TILES / 2;
	const int OFFSET_Y = TILE_SIZE * Y_TILES / 2;

	Collider* col;
	vector<Obstacle*> blockingTiles;
	//tim
	Tile tiles[X_TILES * Y_TILES] = {
	  CLT,CMT,CRT,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,OLT,OMT,ORT,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,OLM,OMM,OMR,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,OLB,OMB,ORB,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CLM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CLM,
	  CLM,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,
	  CLB,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,CLM,TEL,TEM,TER,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,TEM,


	};


};