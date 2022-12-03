#include "game.h"
#include <iostream>
#include <string>

#include "surface.h"
#include "template.h"

#include "MathFunctions.h"

#include <SDL_events.h>
#include <filesystem>
#include <functional>
using namespace std;
namespace Tmpl8
{
	static Game* gs_Game = nullptr;

	Game::Game() :
		cursor("assets/OriginalAssets/target.tga", 1),
		//passes functions as objects
		playButton("assets/UI/Play_Idle.png", "assets/UI/Play_Pushed.png", vec2(ScreenWidth / 2, ScreenHeight / 2), bind(&Game::ResumeGame, this)),
		exitButton("assets/UI/Cross_Idle.png", "assets/UI/Cross_Pushed.png", vec2(ScreenWidth / 2, ScreenHeight / 2 + 64), bind(&Game::ExitGame, this)),
		screen(nullptr),
		currentState(GameState::mainMenu)

	{
		gs_Game = this;

	}

	Game& Game::Get()
	{
		return *gs_Game;
	}

	void Game::Init()
	{
#ifdef _DEBUG
		currentState = GameState::game;
#endif

		Initializations();


		AddInstancesToUpdates();
	}
	float angle = 90;
	void Game::Initializations()
	{
		vec2 centerOfTheScreen = vec2(ScreenWidth / 2, ScreenHeight / 2);
		//reset the score
		score.Init();

		tileMap.Init(centerOfTheScreen);
		player.Init(tileMap.GetCol(), centerOfTheScreen);
		waveSpawner.Init();

		/*col = Collider({ 250 + MathFunctions::GetVec2FromAngle(angle).x * 100,250 + MathFunctions::GetVec2FromAngle(angle).y * 100 }, { 0,0 }, new vec2{ 250,250 });
		col.type = Collider::Type::Projectile;*/
		//AddCollider(&col);

	}
	void Game::ResetGame()
	{

		Shutdown();
		RemoveAllUpdateables();
		Initializations();
		AddInstancesToUpdates();
		ChangeGameState(GameState::mainMenu);
		CheckButtons(static_cast<int>(cursor.pos.x), static_cast<int>(cursor.pos.y));
	}
	void Game::RemoveAllUpdateables()
	{
		RemoveSubject(waveSpawner, player);
		RemoveSubject(waveSpawner, score);
		//player can add a multipler to the score
		RemoveSubject(player, score);

		colliders.clear();
		moveablesTile.clear();
		updateables.clear();
		renderables.clear();
	}

	void Game::AddInstancesToUpdates()
	{


		updateables.push_back(&tileMap);
		renderables.push_back(&tileMap);


		updateables.push_back(&waveSpawner);
		renderables.push_back(&waveSpawner);
		//assign subjects to observers
		//order is important because player has to also sent events to score
		AssignSubject(waveSpawner, player);
		AssignSubject(waveSpawner, score);
		//player can add a multipler to the score
		AssignSubject(player, score);

		updateables.push_back(&player);
		renderables.push_back(&player);


	}
	void Game::AssignSubject(Subject& subject, Observer& observer)
	{
		subject.addObserver(&observer);
	}
	void Game::RemoveSubject(Subject& subject, Observer& observer)
	{
		subject.removeObserver(&observer);

	}
	void Game::Shutdown()
	{
	}


	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f; //make time into seconds
		screen->Clear(0);

		vec2 pos = { 250,400 };

		switch (currentState)
		{
		case GameState::game:
			projectileDetection.Update(deltaTime);

			//movement offset
			for (int i = 0; i < updateables.size(); i++)
				updateables[i]->Update(deltaTime);
			//update the offset to the other entities
			for (int i = 0; i < moveablesTile.size(); i++) {
				moveablesTile[i]->Translation(tileMap.GetOffset());
			}

			//reset the offsets
			tileMap.ResetOffset();
			player.ResetOffset();
			//shooting
			if (player.GetMoveable()->CanRotate())
				player.Rotate(static_cast<int>(cursor.pos.x), static_cast<int>(cursor.pos.y));
			player.Shoot(isPressingLeftMouse);
			//rendering
			for (int i = 0; i < renderables.size(); i++)
				renderables[i]->Render(screen);


			screen->Line(pos.x - cos((angle + 90) * PI / 180) * 100,
				pos.y - sin((angle + 90) * PI / 180) * 100,
				pos.x + cos((angle + 90) * PI / 180) * 100,
				pos.y + sin((angle + 90) * PI / 180) * 100, 0xFF00FF);
			screen->Line(pos.x, pos.y, pos.x + cos(angle * PI / 180) * 100, pos.y + sin(angle * PI / 180) * 100, 0xFF00FF);


			screen->Print(std::to_string(score.getTotal()).c_str(), ScreenWidth - 30, 20, 0x00FF00);
			break;
		case GameState::mainMenu:
			//update main menu stuff;
		case GameState::paused:
			//pause stuff menu
			playButton.Render(screen);
			exitButton.Render(screen);
			break;
		case GameState::reset:
			ResetGame();
			break;
		default:
			break;
		}
		cursor.Render(screen);
	}


	void Game::MouseUp(int button)
	{
		switch (currentState)
		{
		case GameState::mainMenu:
		case GameState::paused:
			playButton.OnMouseUp(button);
			exitButton.OnMouseUp(button);
			break;
		}
		isPressingLeftMouse = false;
	}
	void Game::MouseDown(int button)
	{

		isPressingLeftMouse = true;
	}
	void Game::MouseMove(int x, int y)
	{
		cursor.ChangePosition(x, y);
		switch (currentState)
		{
		case GameState::game:

			player.Rotate(x, y);

			angle = MathFunctions::GetDirInDegreesPositive({ player.GetDir().x ,player.GetDir().y });
			break;
		case GameState::paused:
		case GameState::mainMenu:
			CheckButtons(x, y);
			break;
		}
	}

	void Game::CheckButtons(int x, int y)
	{
		playButton.OnMouseMoved(x, y);
		exitButton.OnMouseMoved(x, y);
	}

	void Game::KeyUp(SDL_Scancode key)
	{

		switch (key)
		{
		case SDL_SCANCODE_W:
			player.GetMoveable()->setUp();

			break;
		case SDL_SCANCODE_S:
			player.GetMoveable()->setDown();

			break;
		case SDL_SCANCODE_D:
			player.GetMoveable()->setRight();

			break;
		case SDL_SCANCODE_A:
			player.GetMoveable()->setLeft();

			break;
		case SDL_SCANCODE_SPACE:
			player.GetMoveable()->setDash();

			break;
		case SDL_SCANCODE_LSHIFT:
			isPressingLeftMouse = false;

			break;
		default:
			break;
		}
	}
	void Game::KeyDown(SDL_Scancode key)
	{
		switch (key)
		{
			//dash
		case SDL_SCANCODE_SPACE:
			player.GetMoveable()->setDash(true);
			break;

		case SDL_SCANCODE_W:
			player.GetMoveable()->setUp(true);
			break;
		case SDL_SCANCODE_S:
			player.GetMoveable()->setDown(true);
			break;
		case SDL_SCANCODE_D:
			player.GetMoveable()->setRight(true);
			break;
		case SDL_SCANCODE_A:
			player.GetMoveable()->setLeft(true);
			break;


			//firerate
		case SDL_SCANCODE_UP:
			player.GetSpawner()->ChangeFireSpeed(FIRE_SPEED_CHANGE);
			break;
		case SDL_SCANCODE_DOWN:
			player.GetSpawner()->ChangeFireSpeed(-FIRE_SPEED_CHANGE);
			break;
		case SDL_SCANCODE_LSHIFT:
			isPressingLeftMouse = true;

			break;
		case SDL_SCANCODE_ESCAPE:
			if (currentState == GameState::game) {
				ChangeGameState(GameState::paused);
				//need update the cursor movement for the buttons
				playButton.OnMouseMoved(static_cast<int>(cursor.pos.x), static_cast<int>(cursor.pos.y));
				exitButton.OnMouseMoved(static_cast<int>(cursor.pos.x), static_cast<int>(cursor.pos.y));
			}
			break;
		default:
			break;
		}
	}
	void Game::ChangeGameState(GameState state)
	{
		currentState = state;
	}
	const Tilemap& Game::getTilemap()
	{
		return tileMap;
	}
	const Game::GameState Game::getCurrentState()
	{
		return currentState;
	}

	const Player& Game::getPlayer()
	{
		return player;
	}

	vector<Collider*>& Game::getColliders()
	{
		return colliders;
	}
	void Game::ResumeGame()
	{
		Game::Get().isPressingLeftMouse = false;
		Game::Get().currentState = Game::GameState::game;
	}
	void Game::ExitGame()
	{
		if (Game::Get().isPressingLeftMouse)
		{
			SDL_Event quit;
			quit.type = SDL_QUIT;
			SDL_PushEvent(&quit);
		}
	}
	void Game::AddCollider(Collider* col)
	{
		colliders.push_back(col);
	}
	void Game::AddMoveable(Moveable* col)
	{
		moveablesTile.push_back(col);
	}
	void Game::RemoveMoveable(Moveable* col)
	{
		moveablesTile.erase(remove(moveablesTile.begin(), moveablesTile.end(), col), moveablesTile.end());
	}
	void Game::RemoveCollider(Collider* col)
	{
		colliders.erase(remove(colliders.begin(), colliders.end(), col), colliders.end());

	}
};