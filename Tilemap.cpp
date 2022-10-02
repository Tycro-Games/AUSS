#include "Tilemap.h"

Tilemap::Tilemap() :
	tileSurface("assets/Holiday/RTSpack_tilesheet@2.png")
{
	tiles.push_back(SNOW_TILE);
}


Tilemap::~Tilemap()
{
}

void Tilemap::Render(Tmpl8::Surface* screen)
{

	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
		{
			int tx = tiles[x].x;
			int ty = tiles[0].y;
			DrawTile(screen, tx, ty, x * TILE_SIZE, y * TILE_SIZE);
		}
}


void Tilemap::Update(float deltaTime)
{
}

void Tilemap::DrawTile(Tmpl8::Surface* screen, int tx, int ty, int x, int y)
{
	Tmpl8::Pixel* src = tileSurface.GetBuffer() + tx * TILE_SIZE + ty * TILE_SIZE * tileSurface.GetPitch();
	Tmpl8::Pixel* dst = screen->GetBuffer() + x + y * 800;
	for (int i = 0; i < TILE_SIZE; i++, src += tileSurface.GetPitch(), dst += screen->GetPitch())//go to the next line
		for (int j = 0; j < TILE_SIZE; j++)//tile size
			dst[j] = src[j];
}
