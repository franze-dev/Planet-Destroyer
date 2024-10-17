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

	static void FollowMouse(SpaceShip& ship)
	{
		Vector2 mousePos = GetMousePosition();

		ship.dir = Vector2Subtract(mousePos, ship.collisionShape.pos);

		//tanf returns result in radians
		ship.angle = atan(ship.dir.y / ship.dir.x);

		//I turn it into DEG so it's compatible with raylib functions
		ship.angle *= 180.0f / PI;

		Quadrant myQuadrant = GetQuadrant(ship.dir);

		if (myQuadrant != Q1)
			FixTanValue(ship.angle, myQuadrant);
	}

	static void MovePos(SpaceShip& ship)
	{
		/*ship.sprite.dest.x += ship.speed.x * GetFrameTime();
		ship.sprite.dest.y += ship.speed.y * GetFrameTime();*/

		ship.collisionShape.pos.x += ship.speed.x * GetFrameTime();
		ship.collisionShape.pos.y += ship.speed.y * GetFrameTime();
	}

	static void MoveShip(SpaceShip& ship)
	{
		Vector2 normalizedDir{};

		float mag = 0.0f;

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			normalizedDir.x = ship.dir.x / sqrt(pow(ship.dir.x, 2.0f) + pow(ship.dir.y, 2.0f));
			normalizedDir.y = ship.dir.y / sqrt(pow(ship.dir.x, 2.0f) + pow(ship.dir.y, 2.0f));

			if (ship.speed.x * ship.speed.x + ship.speed.y * ship.speed.y > ship.maxSpeed * ship.maxSpeed)
			{
				/*Vector2 Math::Normalize(const Vector2 & A, const float Mag) {
					return { A.x / Mag, A.y / Mag };
				}



				Vector2 Math::Multiply(const Vector2 & A, const float K) {
					return { A.x * K, A.y * K };
				}*/

				mag = sqrt(pow(ship.speed.x, 2.0f) + pow(ship.speed.y, 2.0f));

				ship.speed.x /= mag;
				ship.speed.y /= mag;

				ship.speed.x *= ship.maxSpeed;
				ship.speed.y *= ship.maxSpeed;

				cout << sqrt(pow(ship.speed.x, 2.0f) + pow(ship.speed.y, 2.0f)) << endl;
			}

			ship.speed.x += ship.acceleration * normalizedDir.x;
			ship.speed.y += ship.acceleration * normalizedDir.y;

			//cout << "X: " << ship.speed.x << ", Y: " << ship.speed.y << endl;
		}

		MovePos(ship);
		//ship.collisionShape.pos.x += ship.speedIncrease * GetFrameTime();
	}

	static void UpdateSpritePos(SpaceShip& ship)
	{
		ship.sprite.dest.x = ship.collisionShape.pos.x - ship.sprite.texture.width / 2;
		ship.sprite.dest.y = ship.collisionShape.pos.y - ship.sprite.texture.height / 2;
	}

	//static void Reload(SpaceShip& ship)
	//{
	//	/*for (int i = 0; i < maxAmmo; i++)
	//	{
	//		ship.bullets[i] = Bullet::GetBullet();
	//	}*/
	//	return;
	//}

	static void ScreenWrapCheck(SpaceShip& ship)
	{
		//Top or bottom?
		if (ship.collisionShape.pos.y - ship.sprite.texture.height > screenHeight || ship.collisionShape.pos.y + ship.sprite.texture.height < 0)
		{
			//Top (tp to bottom)
			if (ship.collisionShape.pos.y + ship.sprite.texture.height < 0)
				ship.collisionShape.pos.y = static_cast<float>(screenHeight) + static_cast<float>(ship.sprite.texture.height);
			
			//Bottom (tp to top)
			if (ship.collisionShape.pos.y - ship.sprite.texture.height > screenHeight)
				ship.collisionShape.pos.y = -(static_cast<float>(ship.sprite.texture.height));

		}

		//Left or right?
		if (ship.collisionShape.pos.x - ship.sprite.texture.width > screenWidth || ship.collisionShape.pos.x + ship.sprite.texture.width < 0)
		{
			//Left (tp to right)
			if (ship.collisionShape.pos.x + ship.sprite.texture.width < 0)
				ship.collisionShape.pos.x = static_cast<float>(screenWidth) + static_cast<float>(ship.sprite.texture.width);

			//Right (tp to left)
			if (ship.collisionShape.pos.x - ship.sprite.texture.width > screenWidth)
				ship.collisionShape.pos.x = -(static_cast<float>(ship.sprite.texture.width));
			
		}

	}

	SpaceShip GetShip()
	{
		SpaceShip ship;

		ship.sprite.textureDir = TextureManager::shipSprite;
		ship.angle = 0.0f;
		ship.scale = 2;
		ship.maxSpeed = 500.0f;
		ship.acceleration = 100.0f;
		ship.speed = { 0, 0 };

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

		ship.collisionShape.pos.x = (static_cast<float>(screenWidth) / 2.0f);
		ship.collisionShape.pos.y = (static_cast<float>(screenHeight) / 2.0f);
	}

	void Update(SpaceShip& ship)
	{
		FollowMouse(ship);

		MoveShip(ship);

		ScreenWrapCheck(ship);

		UpdateSpritePos(ship);
	}

	void Draw(SpaceShip ship)
	{
		DrawTexturePro(ship.sprite.texture, ship.sprite.source, ship.sprite.dest, ship.sprite.origin, ship.angle, WHITE);
	}
}
