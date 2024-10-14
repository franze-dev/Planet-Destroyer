#include "ship.h"

#include <cmath>
#include "raymath.h"

#include "texture_manager.h"
#include "constants.h"

namespace SpaceShip
{
	enum Quadrant
	{
		Q1,
		Q2,
		Q3,
		Q4
	};

	static Quadrant GetQuadrant(Vector2 shipDir)
	{
		if (shipDir.y > 0 && shipDir.x > 0)
			return Q1;
		else if (shipDir.x < 0 && shipDir.y > 0)
			return Q2;
		else if (shipDir.x < 0 && shipDir.y < 0)
			return Q3;
		else if (shipDir.x > 0 && shipDir.y < 0)
			return Q4;

		return Q1;
	}

	static void FixTanValue(float& angle, Quadrant quadrant)
	{
		switch (quadrant)
		{
		case Q2:
		case Q3:
			angle += 180;
			break;
		case Q4:
			angle += 360;
			break;
		default:
			break;
		}
	}

	SpaceShip GetShip()
	{
		SpaceShip ship;

		ship.sprite.textureDir = TextureManager::shipSprite;
		ship.angle = 0.0f;
		ship.scale = 2;
		ship.maxSpeed = 200.0f;
		ship.speedIncrease = 20.0f;
		ship.modifiableSpeed = { 0, 0 };

		Rectangle sourceRect;

		sourceRect.x = 0;
		sourceRect.y = 0;

		ship.sprite.source = sourceRect;

		Rectangle destRect{};

		destRect.x = screenWidth / 2;
		destRect.y = screenHeight / 2;

		ship.sprite.dest = destRect;

		Vector2 origin{};

		ship.sprite.origin = origin;

		return ship;
	}

	void SaveTexture(Texture2D texture, SpaceShip& ship)
	{
		ship.sprite.texture = texture;

		ship.sprite.source.width = static_cast<float>(ship.sprite.texture.width);
		ship.sprite.source.height = static_cast<float>(ship.sprite.texture.height);

		ship.sprite.dest.width = ship.sprite.source.width * ship.scale;
		ship.sprite.dest.height = ship.sprite.source.height * ship.scale;

		ship.sprite.origin = { static_cast<float>(ship.sprite.texture.width),static_cast<float>(ship.sprite.texture.height) };

		ship.collisionShape.pos.x = (static_cast<float>(screenWidth) / 2.0f) - static_cast<float>(ship.sprite.texture.width);
		ship.collisionShape.pos.y = (static_cast<float>(screenHeight) / 2.0f) - static_cast<float>(ship.sprite.texture.height);
	}

	void Update(SpaceShip& ship)
	{
		FollowMouse(ship);
	}

	void Draw(SpaceShip ship)
	{
		DrawTexturePro(ship.sprite.texture, ship.sprite.source, ship.sprite.dest, ship.sprite.origin, ship.angle, WHITE);
	}

	void FollowMouse(SpaceShip& ship)
	{
		Vector2 mousePos = GetMousePosition();

		Vector2 shipDir = Vector2Subtract(mousePos, ship.collisionShape.pos);

		//tanf returns result in radians
		ship.angle = atan(shipDir.y / shipDir.x);

		//I turn it into DEG so it's compatible with raylib functions
		ship.angle *= 180.0f / PI;

		Quadrant myQuadrant = GetQuadrant(shipDir);

		if (myQuadrant != Q1)
			FixTanValue(ship.angle, myQuadrant);

		cout << ship.angle << endl;
	}
}
