#include "planet.h"

#include <vector>
#include "raymath.h"

#include "screen_info.h"


namespace Planet
{
	enum PlanetType
	{
		earth,
		jupiter,
		mars,
		neptune,
		saturn,
		uranus,
		venus
	};

	enum Position
	{
		left,
		right,
		top,
		bottom
	};

	struct PlanetTexture
	{
		Texture2D texture1;
		Texture2D texture2;
	};

	static const int startPlanets = 50;

	//static vector<Planet> planets;

	//static Planet* planets;

	static Planet planets[startPlanets];

	static Texture2D planetTextures[venus + 1];

	static void SaveTextures(Texture2D texture, Planet& planet)
	{
		planet.sprite.texture = texture;

		planet.sprite.source.width = static_cast<float>(planet.sprite.texture.width);
		planet.sprite.source.height = static_cast<float>(planet.sprite.texture.height);

		planet.sprite.dest.width = planet.sprite.source.width * planet.scale;
		planet.sprite.dest.height = planet.sprite.source.height * planet.scale;

		planet.sprite.origin = { static_cast<float>(planet.sprite.texture.width),static_cast<float>(planet.sprite.texture.height) };

		planet.collisionShape.radius = planet.sprite.texture.height;
	}

	static void InitSprite(TextureManager::Sprite sprite)
	{
		Rectangle sourceRect;

		sourceRect.x = 0;
		sourceRect.y = 0;

		sprite.source = sourceRect;

		Rectangle destRect{};

		destRect.x = 0;
		destRect.y = 0;

		sprite.dest = destRect;

		Vector2 origin{};

		sprite.origin = origin;
	}

	static void RandomizePos(Planet& planet)
	{
		Position pos = static_cast<Position>(GetRandomValue(0, bottom + 1));
		int randomPos = 0;

		switch (pos)
		{
		case left:
			planet.collisionShape.pos.x = -(static_cast<float>(planet.sprite.texture.width));
			randomPos = static_cast<Position>(GetRandomValue(0, screenHeight));
			planet.collisionShape.pos.y = static_cast<float>(randomPos);

			break;
		case right:
			planet.collisionShape.pos.x = screenWidth;
			randomPos = static_cast<Position>(GetRandomValue(0, screenHeight));
			planet.collisionShape.pos.y = static_cast<float>(randomPos);

			break;
		case top:

			randomPos = static_cast<Position>(GetRandomValue(0, screenWidth));
			planet.collisionShape.pos.x = static_cast<float>(randomPos);
			planet.collisionShape.pos.y = -(static_cast<float>(planet.sprite.texture.height));

			break;
		case bottom:
			randomPos = static_cast<Position>(GetRandomValue(0, screenWidth));
			planet.collisionShape.pos.x = static_cast<float>(randomPos);
			planet.collisionShape.pos.y = screenHeight;

			break;
		default:
			break;
		}

	}

	static Planet GetPlanet()
	{
		Planet planet{};

		planet.damage = 1;
		planet.maxSpeed = 100.0f;
		planet.speed = { planet.maxSpeed , planet.maxSpeed };
		planet.scale = 2;
		planet.isSmaller = false;
		planet.lives = 2;
		planet.angle = 0;

		InitSprite(planet.sprite);

		return planet;
	}

	static void DirectionatePlanet(Planet& planet)
	{
		int x = GetRandomValue(0, screenWidth);
		int y = GetRandomValue(0, screenHeight);

		Vector2 objective{ static_cast<float>(x), static_cast<float>(y) };

		/*if (planet.collisionShape.pos.x < 0)
			objective.x = planet.collisionShape.pos.x + planet.speed.x;
		else if(planet.collisionShape.pos.x > screenWidth)
			objective.x = planet.collisionShape.pos.x - planet.speed.x;

		if (planet.collisionShape.pos.y < 0)
			objective.y = planet.collisionShape.pos.y + planet.speed.y;
		else if (planet.collisionShape.pos.x > screenHeight)
			objective.y = planet.collisionShape.pos.y - planet.speed.y;*/


		planet.dir = Vector2Subtract(objective, { planet.collisionShape.pos.x, planet.collisionShape.pos.y });

	}

	/*static Planet GetSmallerPlanet(Planet planet)
	{
		Planet smallPlanet = planet;

		smallPlanet.sprite.dest.width /= 2.0f;
		smallPlanet.sprite.dest.height /= 2.0f;
		smallPlanet.collisionShape.radius /= 2;

		DirectionatePlanet(smallPlanet);

		return smallPlanet;
	}*/

	static void UpdateSpritePos(Planet& planet)
	{
		planet.sprite.dest.x = planet.collisionShape.pos.x;
		planet.sprite.dest.y = planet.collisionShape.pos.y;
	}

	static void MovePlanet(Planet& planet)
	{
		Vector2 normalizedDir{};

		normalizedDir.x = planet.dir.x / sqrt(pow(planet.dir.x, 2.0f) + pow(planet.dir.y, 2.0f));
		normalizedDir.y = planet.dir.y / sqrt(pow(planet.dir.x, 2.0f) + pow(planet.dir.y, 2.0f));

		planet.collisionShape.pos.x += planet.speed.x * normalizedDir.x * GetFrameTime();
		planet.collisionShape.pos.y += planet.speed.y * normalizedDir.y * GetFrameTime();
	}

	static void RandomizeTexture(Planet& planet)
	{
		PlanetType planetType = static_cast<PlanetType>(GetRandomValue(0, venus + 1));

		Texture2D texture;

		switch (planetType)
		{
		case earth:
			texture = planetTextures[earth];

			break;
		case jupiter:
			texture = planetTextures[jupiter];

			break;
		case mars:
			texture = planetTextures[mars];

			break;
		case neptune:
			texture = planetTextures[neptune];

			break;
		case saturn:
			texture = planetTextures[saturn];

			break;
		case uranus:
			texture = planetTextures[uranus];

			break;
		case venus:
			texture = planetTextures[venus];

			break;
		default:
			texture = planetTextures[earth];

			break;
		}

		SaveTextures(texture, planet);


	}

	static void InitPlanet(Planet& planet)
	{
		planet = GetPlanet();
		RandomizeTexture(planet);
		RandomizePos(planet);
		UpdateSpritePos(planet);
		DirectionatePlanet(planet);
	}

	static void InitPlanets()
	{
		for (int i = 0; i < startPlanets; i++)
			InitPlanet(planets[i]);
		
	}

	static void ScreenWrapCheck(Planet& planet)
	{
		//Top or bottom?
		if (planet.collisionShape.pos.y - planet.sprite.texture.height > screenHeight || planet.collisionShape.pos.y + planet.sprite.texture.height < 0)
		{
			//Top (tp to bottom)
			if (planet.collisionShape.pos.y + planet.sprite.texture.height < 0)
				planet.collisionShape.pos.y = static_cast<float>(screenHeight) + static_cast<float>(planet.sprite.texture.height);

			//Bottom (tp to top)
			if (planet.collisionShape.pos.y - planet.sprite.texture.height > screenHeight)
				planet.collisionShape.pos.y = -(static_cast<float>(planet.sprite.texture.height));

		}

		//Left or right?
		if (planet.collisionShape.pos.x - planet.sprite.texture.width > screenWidth || planet.collisionShape.pos.x + planet.sprite.texture.width < 0)
		{
			//Left (tp to right)
			if (planet.collisionShape.pos.x + planet.sprite.texture.width < 0)
				planet.collisionShape.pos.x = static_cast<float>(screenWidth) + static_cast<float>(planet.sprite.texture.width);

			//Right (tp to left)
			if (planet.collisionShape.pos.x - planet.sprite.texture.width > screenWidth)
				planet.collisionShape.pos.x = -(static_cast<float>(planet.sprite.texture.width));

		}
	}

	static void MovePlanets()
	{
		for (int i = 0; i < startPlanets; i++)
		{
			if (planets[i].lives > 0)
			{
				MovePlanet(planets[i]);
				ScreenWrapCheck(planets[i]);
				UpdateSpritePos(planets[i]);
			}
		}

	}

	static void DrawPlanet(Planet planet)
	{
		DrawCircle(static_cast<int>(planet.collisionShape.pos.x), static_cast<int>(planet.collisionShape.pos.y), static_cast<float>(planet.collisionShape.radius), RED);
		DrawTexturePro(planet.sprite.texture, planet.sprite.source, planet.sprite.dest, planet.sprite.origin, static_cast<float>(planet.angle), WHITE);
	}

	static void DrawPlanets()
	{
		for (int i = 0; i < startPlanets; i++)
			if (planets[i].lives > 0)
				DrawPlanet(planets[i]);

	}

	static int GetPlanetsCount()
	{
		int count = 0;
		for (int i = 0; i < startPlanets; i++)
			if (planets[i].lives > 0)
				count++;
		return count;
	}

	static void ReplenishPlanetsCheck()
	{
		if (GetPlanetsCount() <= (startPlanets / 2))
			for (int i = 0; i < startPlanets; i++)
				if (planets[i].lives == 0)
					InitPlanet(planets[i]);
				
	}

	static void DeletePlanet(Planet& planet)
	{
		planet.lives = 0;
	}

	static void ShipCollisionCheck(SpaceShip::SpaceShip& ship, Planet& planet)
	{
		SpaceShip::SpaceShip myship = ship;

		float distX = ship.collisionShape.pos.x - planet.collisionShape.pos.x;
		float distY = ship.collisionShape.pos.y - planet.collisionShape.pos.y;

		float distance = sqrt((distX * distX) + (distY * distY));

		if (distance <= ship.collisionShape.radius + planet.collisionShape.radius)
		{
			DeletePlanet(planet);
			ship.lives--;
			//lose a life!
			//planet divides!
		}

	}

	static void ShipCollisionCheck(SpaceShip::SpaceShip& ship)
	{
		for (int i = 0; i < startPlanets; i++)
			if (planets[i].lives > 0)
				ShipCollisionCheck(ship, planets[i]);


	}

	void LoadTextures()
	{
		planetTextures[earth] = LoadTexture(TextureManager::earthSprite.data());

		planetTextures[venus] = LoadTexture(TextureManager::venusSprite.data());

		planetTextures[saturn] = LoadTexture(TextureManager::saturnSprite.data());

		planetTextures[uranus] = LoadTexture(TextureManager::uranusSprite.data());

		planetTextures[mars] = LoadTexture(TextureManager::marsSprite.data());

		planetTextures[neptune] = LoadTexture(TextureManager::neptuneSprite.data());

		planetTextures[jupiter] = LoadTexture(TextureManager::jupiterSprite.data());

	}

	void UnloadTextures()
	{
		for (int i = 0; i < venus + 1; i++)
			UnloadTexture(planetTextures[i]);

	}

	void Init()
	{
		InitPlanets();
	}

	void Update(SpaceShip::SpaceShip& ship)
	{
		ReplenishPlanetsCheck();
		MovePlanets();
		ShipCollisionCheck(ship);
	}

	void Draw()
	{
		DrawPlanets();
	}
}


