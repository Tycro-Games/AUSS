#include "Tilemap.h"

#include "game.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
Tilemap::Tilemap() :
	tileSurface("assets/Spaceship-shooter#01/Wang tiles/02-Craters.png"),
	pos(Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2)),
	col(new Collider(
		Tmpl8::vec2(0),
		Tmpl8::vec2(0),
		&pos))
{
	lastPos = pos;
	prop = new ParallaxProp(new Tmpl8::Sprite(new Tmpl8::Surface("assets/Spaceship-shooter#01/background/Space02.png"), 1),
		Tmpl8::vec2(pos.x - OFFSET_X, pos.y - OFFSET_Y), .5f);
	Tmpl8::Game::AddMoveable(prop->getMover(), &Tmpl8::Game::moveablesTile);
	//add obstacles
	bool LastOneIsBlocking = false;
	for (int y = 0; y < Y_TILES; y++)
		for (int x = 0; x < X_TILES; x++) {
			int index = x + y * X_TILES;

			if (tiles[index].IsBlocking && tiles[index].obs == nullptr) {

				Tmpl8::vec2 p = Tmpl8::vec2(x * tiles[index].xd + pos.x - static_cast<float>(OFFSET_X),
					y * tiles[index].yd + pos.y - static_cast<float>(OFFSET_Y));
				Tmpl8::vec2 offset = Tmpl8::vec2(tiles[index].pivotX, tiles[index].pivotY);
				p += offset;
				//add other obstacles
				int i = x, j = y;
				float xD = static_cast<float>(tiles[index].xd);
				float yD = static_cast<float>(tiles[index].yd);
				Tmpl8::vec2 dimensions = Tmpl8::vec2(xD - tiles[index].dimensionsX, yD - tiles[index].dimensionsY);
				while (tiles[++i + j * X_TILES].IsBlocking) {
					xD = static_cast<float>(tiles[i + j * X_TILES].xd);
					yD = static_cast<float>(tiles[i + j * X_TILES].yd);
					dimensions += Tmpl8::vec2(xD - tiles[i + j * X_TILES].dimensionsX, 0);
				}
				i--;
				while (tiles[i + (++j) * X_TILES].IsBlocking) {
					xD = static_cast<float>(tiles[i + j * X_TILES].xd);
					yD = static_cast<float>(tiles[i + j * X_TILES].yd);
					dimensions += Tmpl8::vec2(0, yD - tiles[i + j * X_TILES].dimensionsY);

				}
				j--;

				tiles[index].obs = new Obstacle(p, Collider(0, dimensions), index);
				for (int l = x; l <= i; l++) {
					for (int m = y; m <= j; m++) {
						if (l + m * X_TILES == index)
							continue;
						tiles[l + m * X_TILES].obs = tiles[index].obs;
					}
				}
				//get to the end of the added obstacle
				x = i + 1;
				blockingTiles.push_back(tiles[index].obs);
				Tmpl8::Game::AddMoveable(tiles[index].obs);

			}

		}
}






Tilemap::~Tilemap()
{
	delete col;
	delete prop;
}

void Tilemap::Render(Tmpl8::Surface* screen)
{

	prop->Render(screen);
	//24x16 tiles
	for (int y = 0; y < Y_TILES; y++)
		for (int x = 0; x < X_TILES; x++)
		{

			int index = x + y * X_TILES;
			//if the tile is blank skip it
			if (!tiles[index].xd || !tiles[index].yd) {
				continue;
			}
			int tx = tiles[index].x;
			int ty = tiles[index].y;
			//uses some offset to center the tilemap

			DrawTile(screen, tx, ty,
				x * tiles[index].xd + static_cast<int>(pos.x) - OFFSET_X,
				y * tiles[index].yd + static_cast<int>(pos.y) - OFFSET_Y);
		}
	//debug

	for (int i = 0; i < blockingTiles.size(); i++) {
		Collider c = *blockingTiles[i]->getColl();
		screen->Box(static_cast<int>(c.min.x + c.pos->x), static_cast<int>(c.min.y + c.pos->y), static_cast<int>(c.max.x + c.pos->x), static_cast<int>(c.max.y + c.pos->y), 0xFF0000);
	}
	auto posText = std::string(std::to_string(pos.x) + " " + std::to_string(pos.y));
	screen->Print(posText.c_str(), 200, 10, 0xFF0000);
}


void Tilemap::Update(float deltaTime)
{
	for (int i = 0; i < blockingTiles.size(); i++) {

		blockingTiles[i]->Update(deltaTime);
	}
}



void Tilemap::SetPos(const Tmpl8::vec2 p)
{
	pos = p;
}

void Tilemap::DrawTile(Tmpl8::Surface* screen, int tx, int ty, int x, int y)
{
	int maxX = x + TILE_SIZE;
	int maxY = y + TILE_SIZE;

	//determine if the tile is offscreen

	if (maxX < 0 || x >= ScreenWidth || maxY < 0 || y >= ScreenHeight)
		return;
	//determine the clipping amount
	int minCX = std::max(0, x);
	int maxCX = std::min(ScreenWidth, maxX);

	int minCY = std::max(0, y);
	int maxCY = std::min(ScreenHeight, maxY);

	//difference of the clipped amount and the actual amount
	int addOffsetMinX = abs(minCX - x);

	int addOffsetMaxX = abs(maxCX - maxX);

	int addOffsetMinY = abs(minCY - y);

	int addOffsetMaxY = abs(maxCY - maxY);

	//add offset to the origin
	tx += addOffsetMinX;
	x += addOffsetMinX;
	ty += addOffsetMinY;
	y += addOffsetMinY;

	//substract the clipped amount from the tile
	int height = TILE_SIZE - addOffsetMaxY - addOffsetMinY;
	int width = TILE_SIZE - addOffsetMaxX - addOffsetMinX;


	//draw tile
	Tmpl8::Pixel* src = tileSurface.GetBuffer() + tx + ty * tileSurface.GetPitch();
	Tmpl8::Pixel* dst = screen->GetBuffer() + x + y * screen->GetPitch();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {

			//memcpy(dst, src, sizeof(Tmpl8::Pixel) * width);
			//check if the pixel we want to copy is opaque
			if ((src[j] & 0xFF000000) >> 24 == 255)
				dst[j] = src[j];

		}
		src += tileSurface.GetPitch();
		dst += screen->GetPitch();

	}
}
bool Tilemap::IsFree(float x, float y)
{
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

bool Tilemap::IsFree(float x, float y, Collider& col)
{
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

const Obstacle* Tilemap::GetObstacle(float x, float y) const
{

	x += OFFSET_X - (pos.x);
	y += OFFSET_Y - (pos.y);
	size_t tx = static_cast<size_t>(x / TILE_SIZE), ty = static_cast<size_t>(y / TILE_SIZE);

	return GetObstacle(tx, ty);
}

const Obstacle* Tilemap::GetObstacle(size_t x, size_t y) const
{
	assert(x < X_TILES);
	assert(y < Y_TILES);
	return tiles[x + y * X_TILES].obs;
}