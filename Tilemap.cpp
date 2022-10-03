#include "Tilemap.h"

Tilemap::Tilemap() :
	tileSurface("assets/Holiday/RTSpack_tilesheet@2.png"),
	pos(new Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2))

{
	//bounds checking
	col = new Collider(
		Tmpl8::vec2(
			static_cast<float>(-offsetX),
			static_cast<float>(-offsetY)),
		Tmpl8::vec2(
			static_cast<float>(offsetX),
			static_cast<float>(offsetY)),
		pos);

	//tiles adding
	//line 1
	tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 2
	tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 3
	tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 4
	tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 5
	tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 6
	tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 7
	tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);
	//line 8
	tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE); tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);	tiles.push_back(SNOW_TILE);




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
				x * tiles[index].xd + static_cast<int>(pos->x) - offsetX,
				y * tiles[index].yd + static_cast<int>(pos->y) - offsetY);
		}
	//debug
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
