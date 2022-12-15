#include "game.h"
#include <string>

#include "template.h"


#include <SDL_events.h>
#include <filesystem>
#include <functional>
#include "AudioPlayer.h"
//capping framerate
//#include <SDL_timer.h>
using namespace std;

namespace Tmpl8
{
	static Game* gs_game = nullptr;

	Game::Game() :
		screen(nullptr),
		//passes functions as objects
		audioPlayer(nullptr),
		currentState(GameState::mainMenu),
		cursor("assets/OriginalAssets/target.tga", 1),
		playButton("assets/UI/Play_Idle.png", "assets/UI/Play_Pushed.png",
			vec2(ScreenWidth / 2.0f, ScreenHeight / 2.0f),
			bind(&Game::ResumeGame, this)),
		exitButton("assets/UI/Cross_Idle.png", "assets/UI/Cross_Pushed.png",
			vec2(ScreenWidth / 2.0f, ScreenHeight / 2.0f + 64.0f), bind(&Game::ExitGame, this)),
		muteButton("assets/UI/Mute_Idle.png", "assets/UI/Mute_Pushed.png",
			vec2(ScreenWidth / 2.0f, ScreenHeight / 2.0f + 128.0f), bind(&Game::MuteSound, this)),
		volumeButton("assets/UI/Volume_2_Idle.png", "assets/UI/Volume_2_Pushed.png",
			vec2(ScreenWidth / 2.0f, ScreenHeight / 2.0f + 128.0f), bind(&Game::MuteSound, this)),
		fadeInOut(std::bind(&Game::ResetGame, this))

	{
		muteButton.Disable();
		gs_game = this;
	}

	Game& Game::Get()
	{
		return *gs_game;
	}

	void Game::Init()
	{
		ChangeGameState(GameState::mainMenu);

#ifdef _DEBUG
		ChangeGameState(GameState::game);
#endif

		Initializations();


		AddInstancesToUpdates();
	}

	void Game::Initializations()
	{
		const auto centerOfTheScreen = vec2(ScreenWidth / 2.0f, ScreenHeight / 2.0f);
		//reset the score
		score.Init();

		tileMap.Init(centerOfTheScreen);
		player.Init(tileMap.GetCol(), centerOfTheScreen);
		waveSpawner.Init();
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
		//player can add a multiplier to the score
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
		//player can add a multiplier to the score
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
		/*capping frame rate*/
		//float fps = countedFrames / (currentTime / 1000.0f);
		//const int frameTick = static_cast<int>(deltaTime);
		//if (frameTick < SCREEN_TICKS_PER_FRAME)
		//{
		//	SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTick);
		//}
		//countedFrames++;
		//currentTime += deltaTime;
		//std::cout << fps << "\n";

		deltaTime /= 1000.0f; //make time into seconds
		screen->Clear(0);


		changedVolumeButtons = false;

		switch (currentState)
		{
		case GameState::game:
			projectileDetection.Update(deltaTime);

			//movement offset
			for (size_t i = 0; i < updateables.size(); i++)
				updateables[i]->Update(deltaTime);
			//update the offset to the other entities
			for (size_t i = 0; i < moveablesTile.size(); i++)
				moveablesTile[i]->Translation(tileMap.GetOffset());


			//reset the offsets
			tileMap.ResetOffset();
			player.ResetOffset();
			//shooting
			if (player.GetMoveable()->CanRotate())
				player.Rotate(static_cast<int>(cursor.pos.x), static_cast<int>(cursor.pos.y));
			player.Shoot(isPressingLeftMouse);
			//rendering
			for (size_t i = 0; i < renderables.size(); i++)
				renderables[i]->Render(screen);


			screen->Print(std::to_string(score.getTotal()).c_str(), ScreenWidth - 30, 20, 0x00FF00);
			break;
		case GameState::mainMenu:
			//update main menu stuff;
		case GameState::paused:
			//pause stuff menu
			playButton.Render(screen);
			exitButton.Render(screen);
			muteButton.Render(screen);
			volumeButton.Render(screen);
			break;
		case GameState::reset:
			//rendering
			for (size_t i = 0; i < renderables.size(); i++)
				renderables[i]->Render(screen);
			//pause stuff menu
			fadeInOut.Update(deltaTime);
			fadeInOut.Draw(screen);

			break;
		}
		cursor.Render(screen);
	}


	void Game::MouseUp(const int button)
	{
		switch (currentState)
		{
		case GameState::mainMenu:
		case GameState::paused:
			playButton.OnMouseUp(button);
			exitButton.OnMouseUp(button);
			muteButton.OnMouseUp(button);
			volumeButton.OnMouseUp(button);
			break;
		case GameState::game: // NOLINT(bugprone-branch-clone)
			break;
		case GameState::reset:
			break;
		}
		isPressingLeftMouse = false;
	}

	void Game::MouseDown(int button)
	{
		isPressingLeftMouse = true;
	}

	void Game::MouseMove(const int x, const int y)
	{
		switch (currentState)
		{
		case GameState::game:
			cursor.ChangePosition(x, y);

			player.Rotate(x, y);

			break;
		case GameState::paused:
		case GameState::mainMenu:
			cursor.ChangePosition(x, y);

			CheckButtons(x, y);
			break;
		case GameState::reset: break;
		}
	}

	void Game::CheckButtons(const int x, const int y)
	{
		playButton.OnMouseMoved(x, y);
		exitButton.OnMouseMoved(x, y);
		muteButton.OnMouseMoved(x, y);
		volumeButton.OnMouseMoved(x, y);
	}

	void Game::KeyUp(const SDL_Scancode key)
	{
		switch (key) // NOLINT(clang-diagnostic-switch-enum)
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

	void Game::KeyDown(const SDL_Scancode key)
	{
		switch (key) // NOLINT(clang-diagnostic-switch-enum)
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
			if (currentState == GameState::game)
			{
				ChangeGameState(GameState::paused);
				//need update the cursor movement for the buttons
				playButton.OnMouseMoved(static_cast<int>(cursor.pos.x), static_cast<int>(cursor.pos.y));
				exitButton.OnMouseMoved(static_cast<int>(cursor.pos.x), static_cast<int>(cursor.pos.y));
				muteButton.OnMouseMoved(static_cast<int>(cursor.pos.x), static_cast<int>(cursor.pos.y));
				volumeButton.OnMouseMoved(static_cast<int>(cursor.pos.x), static_cast<int>(cursor.pos.y));
			}
			break;
		default:
			break;
		}
	}

	void Game::PlaySound(const SoundID id) const
	{
		audioPlayer->PlaySound(id);
	}

	void Game::PlayMusic() const
	{
		audioPlayer->PlayMusic();
	}

	void Game::StopMusic() const
	{
		audioPlayer->PauseMusic();
	}

	void Game::ResetMusic() const
	{
		audioPlayer->StopMusic();
	}

	void Game::ChangeGameState(const GameState state)
	{
		currentState = state;
		switch (state)
		{
		case GameState::mainMenu:
			StopMusic();

			break;
		case GameState::game:
			PlayMusic();

			break;
		case GameState::paused:
			StopMusic();

			break;
		case GameState::reset:
			ResetMusic();
			fadeInOut.Init();
			break;
		}
	}

	const Tilemap& Game::getTilemap()
	{
		return tileMap;
	}

	Game::GameState Game::getCurrentState() const
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
		isPressingLeftMouse = false;
		ChangeGameState(GameState::game);
	}

	void Game::ExitGame() const
	{
		if (isPressingLeftMouse)
		{
			SDL_Event quit{};
			quit.type = SDL_QUIT;
			SDL_PushEvent(&quit);
		}
	}

	void Game::MuteSound()
	{
		if (changedVolumeButtons)
			return;
		if (audioPlayer->IsMuted())
		{
			muteButton.Disable();
			volumeButton.Enable();
			volumeButton.OnMouseMoved(static_cast<int>(cursor.pos.x), static_cast<int>(cursor.pos.y));
		}
		else
		{
			volumeButton.Disable();
			muteButton.Enable();
			muteButton.OnMouseMoved(static_cast<int>(cursor.pos.x), static_cast<int>(cursor.pos.y));
		}
		changedVolumeButtons = true;
		audioPlayer->SwitchMute();
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
