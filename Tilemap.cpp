#include "Tilemap.h"
#include <iostream>
#include <string>
Tilemap::Tilemap() :
	tileSurface("assets/Holiday/RTSpack_tilesheet@2.png"),
	pos(new Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2)),
	startingPos(*pos),
	col(new Collider(
		Tmpl8::vec2(
			0,
			0),
		Tmpl8::vec2(
			1,
			1),
		pos))

{



	//tiles adding
	//line 1
	tiles.push_back(SNOW_TILE2); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 2
	tiles.push_back(SNOW_TILE2); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 3
	tiles.push_back(SNOW_TILE2); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 4
	tiles.push_back(SNOW_TILE2); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 5
	tiles.push_back(SNOW_TILE2); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 6
	tiles.push_back(SNOW_TILE2); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 7
	tiles.push_back(SNOW_TILE2); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 8
	tiles.push_back(SNOW_TILE2); tiles.push_back(SNOW_TILE2); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);




}


Tilemap::~Tilemap()
{
	delete col;
}

void Tilemap::Render(Tmpl8::Surface* screen)
{
	//13x8 tiles
	for (int y = 0; y < Y_TILES; y++)
		for (int x = 0; x < X_TILES; x++)
		{

			int index = x + y * X_TILES;
			int tx = tiles[index].x;
			int ty = tiles[index].y;
			//uses some offset to center the tilemap
			DrawTile(screen, tx, ty,
				x * tiles[index].xd + static_cast<int>(pos->x) - OFFSET_X,
				y * tiles[index].yd + static_cast<int>(pos->y) - OFFSET_Y);
		}
	//debug
	screen->Box(static_cast<int>(pos->x) - OFFSET_X, static_cast<int>(pos->y) - OFFSET_Y,
		static_cast<int>(pos->x) + OFFSET_X, static_cast<int>(pos->y) + OFFSET_Y, 0xFF0000);

	auto posText = std::string(std::to_string(pos->x) + " " + std::to_string(pos->y));
	screen->Print(posText.c_str(), 200, 10, 0xFF0000);
}


void Tilemap::Update(float deltaTime)
{
}

void Tilemap::DrawTile(Tmpl8::Surface* screen, int tx, int ty, int x, int y)
{
	//determine if the tile is offscreen
	int xd = x + TILE_SIZE;
	int yd = y + TILE_SIZE;
	if (!Collider::InGameScreen(Tmpl8::vec2(static_cast<float>(x), static_cast<float>(y)), Collider(Tmpl8::vec2(0),
		Tmpl8::vec2(static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE)))))
		return;

	Tmpl8::Pixel* src = tileSurface.GetBuffer() + tx + ty * tileSurface.GetPitch();
	//determine where to place it on screen
	Tmpl8::Pixel* dst = screen->GetBuffer() + x + y * screen->GetPitch();
	//draw tile
	for (int i = 0; i < TILE_SIZE; i++, src += tileSurface.GetPitch(), dst += screen->GetPitch())//go to the next line
		for (int j = 0; j < TILE_SIZE; j++)//tile size
			dst[j] = src[j];
}
