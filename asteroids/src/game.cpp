#include "game.h"

#include "raylib.h"

#include "gameplay_scene.h"
#include "constants.h"
#include "scene_manager.h"

namespace Game
{
	static void LoadTextures()
	{
		Gameplay::LoadTextures();
	}

	static void UnloadTextures()
	{
		Gameplay::UnloadTextures();
	}

	static void Init()
	{
		LoadTextures();
		Gameplay::Init();
	}

	static void Update()
	{
		switch (SceneManager::GetCurrentScene())
		{
		case SceneManager::Gameplay:
			Gameplay::Update();
			break;
		default:
			break;
		}
	}

	static void Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		switch (SceneManager::GetCurrentScene())
		{
		case SceneManager::Gameplay:
			Gameplay::Draw();
			break;
		default:
			break;
		}

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

