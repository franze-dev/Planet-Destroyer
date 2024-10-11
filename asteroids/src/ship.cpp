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

		return ship;
	}

	void SaveTexture(Texture2D texture, SpaceShip& ship)
	{
		ship.sprite.texture = texture;
	}

	void Update(SpaceShip& ship)
	{
		FollowMouse(ship);
	}

	void Draw(SpaceShip ship)
	{
		DrawTextureEx(ship.sprite.texture, { screenWidth / 2, screenHeight / 2 }, ship.angle, 2, WHITE);
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
	}
}
