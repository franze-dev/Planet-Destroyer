#include "planet.h"

#include <vector>
#include <ctime>

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

	static const int maxPlanets = 50;

	static Planet planets[maxPlanets];

	static PlanetTexture planetTextures[venus + 1];

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
		Position pos = static_cast<Position>(rand() % bottom + 1);
		int randomPos = 0;

		switch (pos)
		{
		case left:
			planet.collisionShape.pos.x = -(static_cast<float>(planet.width));
			randomPos = rand() % screenHeight;
			planet.collisionShape.pos.y = static_cast<float>(randomPos);

			break;
		case right:
			planet.collisionShape.pos.x = screenWidth;
			randomPos = rand() % screenHeight;
			planet.collisionShape.pos.y = static_cast<float>(randomPos);

			break;
		case top:
			
			randomPos = rand() % screenWidth;
			planet.collisionShape.pos.x = static_cast<float>(randomPos);
			planet.collisionShape.pos.y = -(static_cast<float>(planet.height));

			break;
		case bottom:
			randomPos = rand() % screenWidth;
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
		planet.maxSpeed;
		planet.speed = { planet.maxSpeed , planet.maxSpeed };
		planet.scale = 2;
		planet.isComplete = false;
		planet.lives = 2;
		planet.angle1 = 0;
		planet.angle2 = 0;

		InitSprite(planet.part1.sprite);
		InitSprite(planet.part2.sprite);

		return planet;
	}

	static void UpdateSpritePos(Planet& planet)
	{
		planet.part1.sprite.dest.x = planet.collisionShape.pos.x - planet.part1.sprite.dest.width / 2;
		planet.part1.sprite.dest.y = planet.collisionShape.pos.y;

		planet.part2.sprite.dest.x = planet.collisionShape.pos.x + planet.part2.sprite.dest.width / 2;
		planet.part2.sprite.dest.y = planet.collisionShape.pos.y;
	}

	static void SaveTextures(Texture2D texture1, Texture2D texture2, Planet& planet)
	{
		planet.part1.sprite.texture = texture1;
		planet.part2.sprite.texture = texture2;

		planet.part1.sprite.source.width = static_cast<float>(planet.part1.sprite.texture.width);
		planet.part1.sprite.source.height = static_cast<float>(planet.part1.sprite.texture.height);
		planet.part2.sprite.source.width = static_cast<float>(planet.part2.sprite.texture.width);
		planet.part2.sprite.source.height = static_cast<float>(planet.part2.sprite.texture.height);

		planet.part1.sprite.dest.width = planet.part1.sprite.source.width * planet.scale;
		planet.part1.sprite.dest.height = planet.part1.sprite.source.height * planet.scale;
		planet.part2.sprite.dest.width = planet.part2.sprite.source.width * -planet.scale;
		planet.part2.sprite.dest.height = planet.part2.sprite.source.height * planet.scale;

		planet.part1.sprite.origin = { static_cast<float>(planet.part1.sprite.texture.width),static_cast<float>(planet.part1.sprite.texture.height) };
		planet.part2.sprite.origin = { static_cast<float>(planet.part2.sprite.texture.width),static_cast<float>(planet.part2.sprite.texture.height) };

		planet.collisionShape.radius = planet.height;
	}

	static void DirectionatePlanet(Planet& planet)
	{
		Vector2 normalizedDir{};
		Vector2 objective{};

		if (planet.collisionShape.pos.x < 0)
			objective.x = planet.collisionShape.pos.x + planet.speed.x;
		else if(planet.collisionShape.pos.x > screenWidth)
			objective.x = planet.collisionShape.pos.x - planet.speed.x;

		if (planet.collisionShape.pos.y < 0)
			objective.y = planet.collisionShape.pos.y + planet.speed.y;
		else if (planet.collisionShape.pos.x > screenHeight)
			objective.y = planet.collisionShape.pos.y - planet.speed.y;


		planet.dir = Vector2Subtract(objective, { planet.collisionShape.pos.x, planet.collisionShape.pos.y });

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
		PlanetType planetType = static_cast<PlanetType>(rand() % venus + 1);

		PlanetTexture texture;

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

		SaveTextures(texture.texture1, texture.texture2, planet);


	}

	static void InitPlanets()
	{
		for (int i = 0; i < maxPlanets; i++)
		{
			planets[i] = GetPlanet();
			RandomizeTexture(planets[i]);
			RandomizePos(planets[i]);
			UpdateSpritePos(planets[i]);
			DirectionatePlanet(planets[i]);
		}
	}

	static void MovePlanets()
	{
		for (int i = 0; i < maxPlanets; i++)
			MovePlanet(planets[i]);
		
	}

	static void DrawPlanet(Planet planet)
	{
		DrawTexturePro(planet.part1.sprite.texture, planet.part1.sprite.source, planet.part1.sprite.dest, planet.part1.sprite.origin, static_cast<float>(planet.angle1), WHITE);
		DrawTexturePro(planet.part2.sprite.texture, planet.part1.sprite.source, planet.part2.sprite.dest, planet.part2.sprite.origin, static_cast<float>(planet.angle2), WHITE);
	}

	static void DrawPlanets()
	{
		for (int i = 0; i < maxPlanets; i++)
			DrawPlanet(planets[i]);
		
	}

	void LoadTextures()
	{
		planetTextures[earth].texture1 = LoadTexture(TextureManager::earthSprite1.data());
		planetTextures[earth].texture2 = LoadTexture(TextureManager::earthSprite2.data());

		planetTextures[venus].texture1 = LoadTexture(TextureManager::venusSprite1.data());
		planetTextures[venus].texture2 = LoadTexture(TextureManager::venusSprite2.data());

		planetTextures[saturn].texture1 = LoadTexture(TextureManager::saturnSprite1.data());
		planetTextures[saturn].texture2 = LoadTexture(TextureManager::saturnSprite2.data());

		planetTextures[uranus].texture1 = LoadTexture(TextureManager::uranusSprite1.data());
		planetTextures[uranus].texture2 = LoadTexture(TextureManager::uranusSprite2.data());

		planetTextures[mars].texture1 = LoadTexture(TextureManager::marsSprite1.data());
		planetTextures[mars].texture2 = LoadTexture(TextureManager::marsSprite2.data());

		planetTextures[neptune].texture1 = LoadTexture(TextureManager::neptuneSprite1.data());
		planetTextures[neptune].texture2 = LoadTexture(TextureManager::neptuneSprite2.data());

		planetTextures[jupiter].texture1 = LoadTexture(TextureManager::jupiterSprite1.data());
		planetTextures[jupiter].texture2 = LoadTexture(TextureManager::jupiterSprite2.data());


	}

	void UnloadTextures()
	{
		for (int i = 0; i < venus + 1; i++)
		{
			UnloadTexture(planetTextures[i].texture1);
			UnloadTexture(planetTextures[i].texture2);
		}
	}

	void Init()
	{
		InitPlanets();
	}

	void Update()
	{
		MovePlanets();
	}

	void Draw()
	{
		DrawPlanets();
	}
}


