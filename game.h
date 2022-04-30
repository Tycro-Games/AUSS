#pragma once
#include <vector>
#include "Player.h"
#include "Updateable.h"
#include <SDL_Scancode.h>

namespace Tmpl8 {

	class Surface;
	class Game
	{
	public:
		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int x, int y);
		void KeyUp(SDL_Scancode key);
		void KeyDown(SDL_Scancode key);
	private:
		Surface* screen;
		Player* player;
		std::vector<Updateable*> updateables;
		std::vector<Renderable*> renderables;

	};

}; // namespace Tmpl8