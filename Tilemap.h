#pragma once
#include "surface.h"
#include "template.h"

#include "Collider.h"
#include "vector.h"
#include "Renderable.h"
#include "Updateable.h"
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
		return  lastPos - pos;
	}
	void ResetOffset() {
		lastPos = pos;
	}
	Collider* GetCol() {
		return col;
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
	const Tile SNOW_TILE = { false, 0, 0, 128,128 };
	const Tile SNOW_TILE2 = { false, 128,128,128,128 };

	const int X_TILES = 13;
	const int Y_TILES = 8;
	const int TILE_SIZE = 128;
	const int TILEMAP_SIZE = 640;
	//center the tilemap
	const int OFFSET_X = TILE_SIZE * X_TILES / 2;
	const int OFFSET_Y = TILE_SIZE * Y_TILES / 2;

	Collider* col;
	vector<Tile> tiles;

};