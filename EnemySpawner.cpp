#include "EnemySpawner.h"



EnemySpawner::EnemySpawner(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos) :
	Entity(sprite, pos)

	//timer(new Timer(this, timeToSpawn, true)) this will not work, var is not initialized
{
	timer = new Timer(this, timeToSpawn, true);
	Call();
}

EnemySpawner::~EnemySpawner()
{
	delete timer;
}

void EnemySpawner::Update(float deltaTime)
{
	if (timer->isUpdateable)
		timer->Update(deltaTime);
}

void EnemySpawner::Render(Tmpl8::Surface* screen)
{
	sprite->Draw(screen, pos->x, pos->y);
}

void EnemySpawner::Call()
{
	std::cout << "Spawn Enemy\n";
}
