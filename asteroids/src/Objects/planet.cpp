#include "objects/planet.h"

#include <vector>
#include "raymath.h"

#include "utils/screen_info.h"
#include "utils/audio_manager.h"

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

	static Texture2D planetTextures[venus + 1];

	static void SaveTexture(Texture2D texture, Planet& planet)
	{
		if (!IsTextureReady(texture))
			abort();

		planet.sprite.texture = texture;

		planet.sprite.source.width = static_cast<float>(planet.sprite.texture.width);
		planet.sprite.source.height = static_cast<float>(planet.sprite.texture.height);

		planet.sprite.dest.width = planet.sprite.source.width * planet.scale;
		planet.sprite.dest.height = planet.sprite.source.height * planet.scale;

		planet.sprite.origin = { static_cast<float>(planet.sprite.dest.width / 2),static_cast<float>(planet.sprite.dest.height / 2) };

		planet.collisionShape.radius = planet.sprite.texture.height;
	}

	static void InitSprite(TextureManager::Sprite& sprite)
	{
		Rectangle sourceRect{};

		sourceRect.x = 0;
		sourceRect.y = 0;

		sprite.source = sourceRect;

		Rectangle destRect{};

		destRect.x = 0;
		destRect.y = 0;

		sprite.dest = destRect;

		Vector2 origin{};

		origin.x = 0;
		origin.y = 0;

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
			randomPos = GetRandomValue(0, screenHeight);
			planet.collisionShape.pos.y = static_cast<float>(randomPos);

			break;
		case right:
			planet.collisionShape.pos.x = screenWidth;
			randomPos = GetRandomValue(0, screenHeight);
			planet.collisionShape.pos.y = static_cast<float>(randomPos);

			break;
		case top:

			randomPos = GetRandomValue(0, screenWidth);
			planet.collisionShape.pos.x = static_cast<float>(randomPos);
			planet.collisionShape.pos.y = -(static_cast<float>(planet.sprite.texture.height));

			break;
		case bottom:
			randomPos = GetRandomValue(0, screenWidth);
			planet.collisionShape.pos.x = static_cast<float>(randomPos);
			planet.collisionShape.pos.y = screenHeight;

			break;
		default:
			randomPos = GetRandomValue(0, screenWidth);
			planet.collisionShape.pos.x = static_cast<float>(randomPos);
			planet.collisionShape.pos.y = screenHeight;
			break;
		}
	}

	static Planet GetPlanet()
	{
		Planet planet;

		planet.damage = 1;
		planet.maxSpeed = 100.0f;
		planet.speed = { planet.maxSpeed , planet.maxSpeed };
		planet.scale = 2;
		planet.isSmaller = false;
		planet.size = 3;
		planet.angle = 0;
		planet.visible = true;

		InitSprite(planet.sprite);

		return planet;
	}

	static void DirectionatePlanet(Planet& planet)
	{
		int x = GetRandomValue(0, screenWidth);
		int y = GetRandomValue(0, screenHeight);

		Vector2 objective{ static_cast<float>(x), static_cast<float>(y) };

		planet.dir = Vector2Subtract(objective, { planet.collisionShape.pos.x, planet.collisionShape.pos.y });

	}

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
		PlanetType planetType = static_cast<PlanetType>(GetRandomValue(0, venus));

		Texture2D texture = planetTextures[earth];

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
			abort();
			break;
		}

		SaveTexture(texture, planet);


	}

	static void InitPlanet(Planet& planet)
	{
		planet = GetPlanet();
		RandomizeTexture(planet);
		RandomizePos(planet);
		UpdateSpritePos(planet);
		DirectionatePlanet(planet);
	}

	static void InitPlanets(Planet planets[])
	{
		for (int i = 0; i < startPlanets; i++)
			InitPlanet(planets[i]);

		for (int i = startPlanets; i < maxPossiblePlanets; i++)
		{
			InitPlanet(planets[i]);
			planets[i].visible = false;
		}

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

	static void MovePlanets(Planet planets[])
	{
		for (int i = 0; i < maxPossiblePlanets; i++)
		{
			if (planets[i].size > 0 && planets[i].visible)
			{
				MovePlanet(planets[i]);
				ScreenWrapCheck(planets[i]);
				UpdateSpritePos(planets[i]);
			}
		}

	}

	static void DrawPlanet(Planet planet)
	{
		//#ifdef DEBUG
		//DrawCircle(static_cast<int>(planet.collisionShape.pos.x), static_cast<int>(planet.collisionShape.pos.y), static_cast<float>(planet.collisionShape.radius), RED);
		//DrawRectangleLines(static_cast<int>(planet.sprite.dest.x), static_cast<int>(planet.sprite.dest.y), static_cast<int>(planet.sprite.dest.width), static_cast<int>(planet.sprite.dest.height), GREEN);
		//#endif // DEBUG

		if (planet.visible)
		{
			DrawTexturePro(planet.sprite.texture, planet.sprite.source, planet.sprite.dest, planet.sprite.origin, static_cast<float>(planet.angle), WHITE);

		}
	}

	static void DrawPlanets(Planet planets[])
	{
		for (int i = 0; i < maxPossiblePlanets; i++)
			if (planets[i].size > 0 && planets[i].visible)
				DrawPlanet(planets[i]);

	}

	static int GetPlanetsCount(Planet planets[])
	{
		int count = 0;
		for (int i = 0; i < maxPossiblePlanets; i++)
			if (planets[i].size > 0 && planets[i].visible)
				count++;
		return count;
	}

	static void ReplenishPlanetsCheck(Planet planets[])
	{
		if (GetPlanetsCount(planets) <= (maxPossiblePlanets - startPlanets))
			for (int i = 0; i < (maxPossiblePlanets / 2); i++)
				if (planets[i].size == 0)
					InitPlanet(planets[i]);

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
		}

	}

	static void ShipCollisionCheck(SpaceShip::SpaceShip& ship, Planet planets[])
	{
		for (int i = 0; i < startPlanets; i++)
			if (planets[i].size > 0 && planets[i].visible)
				ShipCollisionCheck(ship, planets[i]);


	}

	static Planet GetSmallerPlanet(Planet planet)
	{
		Planet smallPlanet = planet;

		smallPlanet.sprite.dest.width /= 2.0f;
		smallPlanet.sprite.dest.height /= 2.0f;

		smallPlanet.sprite.origin = { static_cast<float>(smallPlanet.sprite.dest.width / 2),static_cast<float>(smallPlanet.sprite.dest.height / 2) };

		smallPlanet.collisionShape.radius /= 2;
		smallPlanet.size--;

		smallPlanet.isSmaller = true;

		DirectionatePlanet(smallPlanet);

		return smallPlanet;
	}

	static void AddPlanet(Planet planetToAdd, Planet planets[])
	{
		for (int i = 0; i < maxPossiblePlanets; i++)
		{
			////if this planet exists, the angle will be zero, because that means it's not a garbage value
			//if (planets[i].angle != 0)
			//	return (i);
			if (!planets[i].visible)
			{
				planets[i] = planetToAdd;
				break;
			}
		}
	}

	void DividePlanet(Planet& planet, Planet planets[])
	{
		Planet firstPlanet = GetSmallerPlanet(planet);
		Planet secondPlanet = GetSmallerPlanet(planet);

		planet = firstPlanet;

		AddPlanet(secondPlanet, planets);
	}

	void LoadTextures()
	{
		planetTextures[earth] = LoadTexture(TextureManager::earthSprite.c_str());

		planetTextures[venus] = LoadTexture(TextureManager::venusSprite.c_str());

		planetTextures[saturn] = LoadTexture(TextureManager::saturnSprite.c_str());

		planetTextures[uranus] = LoadTexture(TextureManager::uranusSprite.c_str());

		planetTextures[mars] = LoadTexture(TextureManager::marsSprite.c_str());

		planetTextures[neptune] = LoadTexture(TextureManager::neptuneSprite.c_str());

		planetTextures[jupiter] = LoadTexture(TextureManager::jupiterSprite.c_str());

	}

	void UnloadTextures()
	{
		for (int i = 0; i < venus + 1; i++)
			UnloadTexture(planetTextures[i]);

	}

	void Init(Planet planets[])
	{
		InitPlanets(planets);
	}

	void Update(SpaceShip::SpaceShip& ship, Planet planets[])
	{
		ReplenishPlanetsCheck(planets);
		MovePlanets(planets);
		ShipCollisionCheck(ship, planets);
	}

	void Draw(Planet planets[])
	{
		DrawPlanets(planets);
	}

	void DeletePlanet(Planet& planet)
	{
		Audio::Play(Audio::Sfx::planet);

		planet.size = 0;
	}
}


