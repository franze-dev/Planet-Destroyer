#include "gameplay_scene.h"

#include "raylib.h"

#include "objects/ship.h"
#include "objects/planet.h"
#include "scenes/pause_menu.h"
#include "utils/scene_manager.h"
#include "utils/audio_manager.h"

namespace Gameplay
{
	SpaceShip::SpaceShip ship;
	static Texture2D shipTexture;
	static bool isPaused = false;

	static void CheckPause()
	{
		if (IsKeyReleased(KEY_P) && !isPaused)
			isPaused = true;
	}

	void UnPauseGame()
	{
		isPaused = false;
	}

	void LoadTextures()
	{
		shipTexture = LoadTexture("res/sprites/spaceship.png");
		Planet::LoadTextures();
	}

	void UnloadTextures()
	{
		UnloadTexture(shipTexture);
		Planet::UnloadTextures();
	}

	void Init()
	{
		isPaused = false;
		ship = SpaceShip::GetShip();
		SpaceShip::SaveTexture(shipTexture, ship);
		Planet::Init();
		PauseMenu::Init();
	}

	void Update()
	{
		CheckPause();

		if (!Audio::IsPlaying(Audio::Song::gameplay))
			Audio::Play(Audio::Song::gameplay);
		
		if (Audio::IsPlaying(Audio::Song::gameplay))
			Audio::Update(Audio::Song::gameplay);
		

		if (SpaceShip::IsAlive(ship))
		{
			if (!isPaused)
			{
				SpaceShip::Update(ship);
				Planet::Update(ship);
			}
			else
				PauseMenu::Update();
		}
		else
		{
			if (Audio::IsPlaying(Audio::Song::gameplay))
				Audio::Stop(Audio::Song::gameplay);
			
			SceneManager::SetCurrentScene(SceneManager::Result);
		}
		
	}

	void Draw()
	{
		SpaceShip::Draw(ship);
		Planet::Draw();

		if (isPaused)
			PauseMenu::Draw();
		
	}
}


