#include "MoveToADirection.h"
#include "game.h"

MoveToADirection::MoveToADirection(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Collider* col, Callable* call, float speed) :
	Moveable(pos, col, speed),
	dir(dir),
	call(call)
{
	dir->normalize();
}

void MoveToADirection::Update(float deltaTime)
{

	Tmpl8::vec2 nextPos = { 0 };
	nextP = *pos;
	nextPos = (*dir) * speed * deltaTime;


	nextP += nextPos;
	//offset by the collider length so it bounces back exactly on the edge
	if (col->InGameBounds(nextP, (*col))) {
		if (Tmpl8::Game::tileMap->IsFree(nextP.x + col->min.x, nextP.y + col->min.y) &&
			Tmpl8::Game::tileMap->IsFree(nextP.x + col->min.x, nextP.y + col->max.y) &&
			Tmpl8::Game::tileMap->IsFree(nextP.x + col->max.x, nextP.y + col->min.y) &&
			Tmpl8::Game::tileMap->IsFree(nextP.x + col->max.x, nextP.y + col->max.y))
			(*pos) = nextP;
		else {
			//reflect on obstacle
		//	Obstacle* obs = Tmpl8::Game::tileMap->GetObstacle(nextP.x + col->min.x, nextP.y + col->min.y);
			Obstacle* obs = Tmpl8::Game::tileMap->GetObstacle(nextP.x + col->min.x, nextP.y + col->min.y);
			Obstacle* obs1 = Tmpl8::Game::tileMap->GetObstacle(nextP.x + col->min.x, nextP.y + col->max.y);
			Obstacle* obs2 = Tmpl8::Game::tileMap->GetObstacle(nextP.x + col->max.x, nextP.y + col->min.y);
			Obstacle* obs3 = Tmpl8::Game::tileMap->GetObstacle(nextP.x + col->max.x, nextP.y + col->max.y);

			if (obs != NULL)
				colToReflectFrom = obs->getColl();
			if (obs1 != NULL)
				colToReflectFrom = obs1->getColl();
			if (obs2 != NULL)
				colToReflectFrom = obs2->getColl();
			if (obs3 != NULL)
				colToReflectFrom = obs3->getColl();


			call->Call();
		}
	}
	else {
		call->Call();
	}


}

MoveToADirection::~MoveToADirection()
{

}
