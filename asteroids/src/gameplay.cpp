#include "gameplay.h"

#include "raylib.h"

#include "constants.h"
#include "ui_manager.h"
#include "ship.h"

namespace Gameplay
{
	UIManager::Text credits;
	SpaceShip::SpaceShip ship;
	static Texture2D shipTexture;

	static void LoadTextures()
	{
		shipTexture = LoadTexture("res/sprites/spaceship.png");

	}

	static void UnloadTextures()
	{

		UnloadTexture(shipTexture);
	}

	static void Init()
	{
		ship = SpaceShip::GetShip();
		LoadTextures();
		SpaceShip::SaveTexture(shipTexture, ship);
	}

	static void Update()
	{
		SpaceShip::Update(ship);
	}

	static void Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		SpaceShip::Draw(ship);

		EndDrawing();
	}

	static void Close()
	{
		UnloadTextures();
	}

	void Play()
	{
		InitWindow(screenWidth, screenHeight, "Planet Destroyer");
		Init();

		while (!WindowShouldClose())
		{
			Update();
			Draw();
		}

		Close();
	}
}

