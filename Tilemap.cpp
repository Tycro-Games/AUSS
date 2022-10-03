#include "Tilemap.h"

Tilemap::Tilemap() :
	tileSurface("assets/Holiday/RTSpack_tilesheet.png"),
	pos(new Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2))

{
	col = new Collider(
		Tmpl8::vec2(
			 - offsetX,
			 - offsetY),
		Tmpl8::vec2(
			offsetX,
			 offsetY),
		pos);

	//tiles adding
	tiles.push_back(SNOW_TILE);
	tiles.push_back(SNOW_TILE);
	tiles.push_back(SNOW_TILE);
	tiles.push_back(SNOW_TILE);
	tiles.push_back(SNOW_TILE);
	tiles.push_back(SNOW_TILE);
	tiles.push_back(SNOW_TILE2);
	tiles.push_back(SNOW_TILE2);
	tiles.push_back(SNOW_TILE2);
	tiles.push_back(SNOW_TILE2);
	tiles.push_back(SNOW_TILE2);
	tiles.push_back(SNOW_TILE2);


}


Tilemap::~Tilemap()
{
	delete col;
}

void Tilemap::Render(Tmpl8::Surface* screen)
{

	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 4; x++)
		{
			int index = x + y * 4;
			int tx = tiles[index].x;
			int ty = tiles[index].y;

			DrawTile(screen, tx, ty,
				x * tiles[index].xd + static_cast<int>(pos->x) - offsetX,
				y * tiles[index].yd + static_cast<int>(pos->y) - offsetY);
		}
	screen->Box(static_cast<int>(pos->x) - offsetX, static_cast<int>(pos->y) - offsetY,
		static_cast<int>(pos->x) + offsetX, static_cast<int>(pos->y) + offsetY, 0xFF0000);
}


void Tilemap::Update(float deltaTime)
{
}

void Tilemap::DrawTile(Tmpl8::Surface* screen, int tx, int ty, int x, int y)
{
	Tmpl8::Pixel* src = tileSurface.GetBuffer() + tx + ty * tileSurface.GetPitch();
	Tmpl8::Pixel* dst = screen->GetBuffer() + x + y * screen->GetPitch();
	for (int i = 0; i < TILE_SIZE; i++, src += tileSurface.GetPitch(), dst += screen->GetPitch())//go to the next line
		for (int j = 0; j < TILE_SIZE; j++)//tile size
			dst[j] = src[j];
}
