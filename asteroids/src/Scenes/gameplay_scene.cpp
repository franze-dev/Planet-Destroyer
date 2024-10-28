#include "gameplay_scene.h"

#include "raylib.h"

#include "objects/ship.h"
#include "objects/planet.h"
#include "objects/button.h"
#include "objects/text.h"
#include "scenes/pause_menu.h"
#include "utils/scene_manager.h"
#include "utils/audio_manager.h"
#include "utils/calculations.h"

namespace Gameplay
{
	Planet::Planet planets[Planet::startPlanets];
	SpaceShip::SpaceShip ship;
	static Texture2D shipTexture;
	static Button::Button pauseButton;
	static bool isPaused = false;

	static void CheckPause()
	{
		if (Button::IsMouseOnButton(pauseButton))
		{
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				isPaused = true;
			}
		}
	}

	static void BulletPlanetCollision(Planet::Planet& planet, Bullet::Bullet& bullet)
	{
		Collide::Distances calculations;

		calculations.pinPointX = static_cast<int>(planet.collisionShape.pos.x);
		calculations.pinPointY = static_cast<int>(planet.collisionShape.pos.y);

		if (static_cast<int>(planet.collisionShape.pos.x) < static_cast<int>(bullet.rect.x))
			calculations.pinPointX = static_cast<int>(bullet.rect.x); //left
		else if (static_cast<int>(planet.collisionShape.pos.x) > static_cast<int>(bullet.rect.x) + static_cast<int>(bullet.rect.width))
			calculations.pinPointX = static_cast<int>(bullet.rect.x) + static_cast<int>(bullet.rect.width); //right

		if (static_cast<int>(planet.collisionShape.pos.y) < static_cast<int>(bullet.rect.y))
			calculations.pinPointY = static_cast<int>(bullet.rect.y); //top
		else if (static_cast<int>(planet.collisionShape.pos.y) > static_cast<int>(bullet.rect.y) + static_cast<int>(bullet.rect.height))
			calculations.pinPointY = static_cast<int>(bullet.rect.y) + static_cast<int>(bullet.rect.height); //bottom

		calculations.distX = static_cast<int>(planet.collisionShape.pos.x) - calculations.pinPointX;
		calculations.distY = static_cast<int>(planet.collisionShape.pos.y) - calculations.pinPointY;
		calculations.distance = static_cast<int>(sqrt((calculations.distX * calculations.distX) + (calculations.distY * calculations.distY)));

		if (calculations.distance <= planet.collisionShape.radius)
		{
			planet.lives = 0;
			bullet.isVisible = false;
		}
	}

	static void BulletPlanetCollision()
	{
		for (int i = 0; i < SpaceShip::maxAmmo; i++)
			if (ship.bullets[i].isVisible)
				for (int j = 0; j < Planet::startPlanets; j++)
					if (planets[j].lives > 0)
						BulletPlanetCollision(planets[j], ship.bullets[i]);
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
		Planet::Init(planets);
		PauseMenu::Init();
		pauseButton = Button::GetButton(static_cast<int>(Text::Padding::small), static_cast<int>(Text::Padding::small), 100.0f, 50.0f, "PAUSE", BLACK, RED, YELLOW, Text::Fonts::Default);
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
				Planet::Update(ship, planets);
				BulletPlanetCollision();
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
		Planet::Draw(planets);

		if (!isPaused)
			Button::DrawButton(pauseButton);
		

		if (isPaused)
			PauseMenu::Draw();

	}
}


