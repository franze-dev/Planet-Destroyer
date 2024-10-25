#include "game.h"

#include <ctime>
#include "raylib.h"

#include "gameplay_scene.h"
#include "menu_scene.h"
#include "screen_info.h"
#include "scene_manager.h"
#include "text.h"
#include "credits_scene.h"
#include "result_scene.h"
#include "audio_manager.h"
//NOTE: All of the above are used

namespace Game
{
	static SceneManager::Scene previousScene = SceneManager::None;
	static bool restart = true;

	static void LoadRes()
	{
		Audio::Load();
		Gameplay::LoadTextures();
	}

	static void UnloadRes()
	{
		Audio::UnLoad();
		Gameplay::UnloadTextures();
	}

	static void Init()
	{
		srand(time(NULL));
		Gameplay::Init();
		MenuScene::Init();
		CreditsScene::Init();
		ResultScene::Init();
	}

	static void Update()
	{
		switch (SceneManager::GetCurrentScene())
		{
		case SceneManager::Gameplay:
			if (previousScene != SceneManager::Gameplay)
				previousScene = SceneManager::Gameplay;
			Gameplay::Update();
			break;
		case SceneManager::Menu:
			MenuScene::Update();
			break;
		case SceneManager::Credits:
			CreditsScene::Update();
			break;
		case SceneManager::Result:
			if (previousScene != SceneManager::Result)
				previousScene = SceneManager::Result;
			ResultScene::Update();
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
		case SceneManager::Result:
			ResultScene::Draw();
			break;
		default:
			break;
		}

		EndDrawing();
	}

	static void Close()
	{
		Text::UnloadFonts();
		UnloadRes();
	}

	static bool ShouldWindowClose()
	{
		return WindowShouldClose() || SceneManager::GetCurrentScene() == SceneManager::None;
	}

	void Play()
	{
		InitWindow(screenWidth, screenHeight, "Planet Destroyer");
		Text::InitFonts();
		LoadRes();
		Init();

		while (!ShouldWindowClose())
		{
			if ((previousScene == SceneManager::Result || (previousScene == SceneManager::Gameplay) &&
				SceneManager::GetCurrentScene() != SceneManager::Result) &&
				SceneManager::GetCurrentScene() != SceneManager::Gameplay)
			{
				restart = true;
				previousScene = SceneManager::None;
			}

			if (restart)
			{
				Init();
				restart = false;
			}

			Update();
			Draw();
		}

		Close();
	}
}

