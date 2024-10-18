#include "game.h"

#include "raylib.h"

#include "gameplay_scene.h"
#include "menu_scene.h"
#include "screen_info.h"
#include "scene_manager.h"
#include "ui_manager.h"
#include "credits_scene.h"

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
		CreditsScene::Init();
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
			break;
		case SceneManager::Credits:
			CreditsScene::Update();
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
		case SceneManager::Menu:
			MenuScene::Draw();
			break;
		case SceneManager::Credits:
			CreditsScene::Draw();
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

