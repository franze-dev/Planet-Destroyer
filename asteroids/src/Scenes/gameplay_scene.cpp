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
#include "utils/screen_info.h"

namespace Gameplay
{
	struct Triangle
	{
		int width; //distance from 1 to 3
		int height; //distance from 1 to 2
		Vector2 vertex1;  //	2
		Vector2 vertex2;  //  /	  \ 
		Vector2 vertex3;  // 1-----3
	};

	static const int maxLives = 6;
	static bool isPaused = false;
	Planet::Planet planets[Planet::startPlanets];
	SpaceShip::SpaceShip ship;
	static Triangle lives[maxLives];
	static Texture2D shipTexture;
	static Button::Button pauseButton;

	static void CheckPause()
	{
		if (Button::IsMouseOnButton(pauseButton))
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				isPaused = true;
			
	}

	static void BulletPlanetCollision(Planet::Planet& planet, Bullet::Bullet& bullet)
	{
		Collide::Distances calculations{};

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
			Planet::DeletePlanet(planet);
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
	
	static Triangle InitLife(float x)
	{
		Triangle life{};

		life.height = 40;
		life.width = life.height / 2;
		life.vertex1 = { x , life.width + static_cast<float>(Text::Padding::small) };
		life.vertex3 = life.vertex1;
		life.vertex3.x += life.width;
		life.vertex2 = { life.vertex1.x + life.width / 2, life.vertex1.y - life.height };

		return life;
	}

	static void InitLives()
	{
		float x = static_cast<float>(Text::Padding::tiny);

		for (int i = 0; i < maxLives; i++)
		{
			lives[i] = InitLife(x);
			x += lives[i].width + static_cast<float>(Text::Padding::tiny);
		}
	}

	static void DrawLife(Triangle life)
	{
		DrawTriangle(life.vertex1, life.vertex3, life.vertex2, WHITE);
	}

	static void DrawLives()
	{
		for (int i = 0; i < ship.lives; i++)
			DrawLife(lives[i]);
		
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
		pauseButton = Button::GetButton(screenWidth, static_cast<int>(Text::Padding::small), 100.0f, 50.0f, "PAUSE", BLACK, RED, YELLOW, Text::Fonts::Default);
		pauseButton.shape.x -= pauseButton.shape.width + static_cast<int>(Text::Padding::small);
		InitLives();
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
		
		if (ship.lives > 0)
			DrawLives();
		

		if (isPaused)
			PauseMenu::Draw();

	}
}


