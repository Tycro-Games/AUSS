#include "EnemySpawner.h"
#include "game.h"

#include "Enemy.h"
using namespace Tmpl8;
using namespace std;

EnemySpawner::EnemySpawner(const vec2 _pos) :
	pos(_pos)

{
	move.Init(&pos);
	Game::Get().AddMoveable(&move);
}


const vec2& EnemySpawner::GetSpawnerPos() const
{
	return pos;
}
