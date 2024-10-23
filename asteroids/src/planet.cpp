#include "planet.h"

#include <vector>
#include "raymath.h"

#include "screen_info.h"

namespace Planet
{
	static Planet planets[];

	static void UpdateSpritePos(Planet& planet)
	{
		planet.sprite.dest.x = planet.collisionShape.pos.x;
		planet.sprite.dest.y = planet.collisionShape.pos.y;
	}

	static Planet GetPlanet()
	{
		Planet planet{};

		planet.damage = 1;
		planet.maxSpeed;
		planet.speed = { planet.maxSpeed , planet.maxSpeed };
		planet.scale = 2;
		planet.isSparePart = false;

		Rectangle sourceRect;

		sourceRect.x = 0;
		sourceRect.y = 0;

		planet.sprite.source = sourceRect;

		Rectangle destRect{};

		destRect.x = 0;
		destRect.y = 0;

		planet.sprite.dest = destRect;

		Vector2 origin{};

		planet.sprite.origin = origin;

		return planet;
	}

	static void SaveTexture(Texture2D texture, Planet& planet)
	{
		planet.sprite.texture = texture;

		planet.sprite.source.width = static_cast<float>(planet.sprite.texture.width);
		planet.sprite.source.height = static_cast<float>(planet.sprite.texture.height);

		planet.sprite.dest.width = planet.sprite.source.width * planet.scale;
		planet.sprite.dest.height = planet.sprite.source.height * planet.scale;

		planet.sprite.origin = { static_cast<float>(planet.sprite.texture.width),static_cast<float>(planet.sprite.texture.height) };

		planet.collisionShape.pos.x = (static_cast<float>(screenWidth) / 2.0f);
		planet.collisionShape.pos.y = (static_cast<float>(screenHeight) / 2.0f);

		planet.collisionShape.radius = static_cast<int>(planet.sprite.dest.width) / 2;
	}

	static void DirectionatePlanet(Planet& planet)
	{
		Vector2 normalizedDir{};
		Vector2 mousePos = GetMousePosition();

		planet.dir = Vector2Subtract(mousePos, { planet.collisionShape.pos.x, planet.collisionShape.pos.y });

		normalizedDir.x = planet.dir.x / sqrt(pow(planet.dir.x, 2.0f) + pow(planet.dir.y, 2.0f));
		normalizedDir.y = planet.dir.y / sqrt(pow(planet.dir.x, 2.0f) + pow(planet.dir.y, 2.0f));

	}

	static void MovePlanet(Vector2 normalizedDir, Planet& planet)
	{
		planet.collisionShape.pos.x += planet.speed.x * normalizedDir.x * GetFrameTime();
		planet.collisionShape.pos.y += planet.speed.y * normalizedDir.y * GetFrameTime();
	}

	void Draw(Planet planet)
	{
		DrawTexturePro(planet.sprite.texture, planet.sprite.source, planet.sprite.dest, planet.sprite.origin, 0, WHITE);
	}

	void Update()
	{

	}
}


