#include "gameplay.h"

#include "raylib.h"

#include "constants.h"

namespace Gameplay
{
	static void Init()
	{

	}

	static void Update()
	{

	}

	static void Draw()
	{

	}

	void Play()
	{
		InitWindow(screenWidth, screenHeight, "Awesome Asteroids");
		Init();

		while (!WindowShouldClose())
		{
			Update();
			Draw();
		}
	}
}

