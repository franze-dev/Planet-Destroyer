#include "game.h"

#include "raylib.h"

#include "gameplay_scene.h"
#include "menu_scene.h"
#include "constants.h"
#include "scene_manager.h"
#include "ui_manager.h"

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
		UIManager::InitFonts();
		LoadTextures();
		Gameplay::Init();
		MenuScene::Init();
	}

	static void Update()
	{
		switch (SceneManager::GetCurrentScene())
		{
		case SceneManager::Gameplay:
			Gameplay::Update();
			break;
		case SceneManager::Menu:
			MenuScene::Update();
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
		case SceneManager::Menu:
			MenuScene::Draw();
		default:
			break;
		}

		EndDrawing();
	}

	static void Close()
	{
		UnloadTextures();
	}

	static bool ShouldWindowClose()
	{
		return WindowShouldClose() || SceneManager::GetCurrentScene() == SceneManager::None;
	}

	void Play()
	{
		InitWindow(screenWidth, screenHeight, "Planet Destroyer");
		Init();

		while (!ShouldWindowClose())
		{
			Update();
			Draw();
		}

		Close();
	}
}

