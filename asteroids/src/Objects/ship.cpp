#include "ship.h"

#include <cmath>
#include "raymath.h"
#include "raylib.h"

#include "utils/texture_manager.h"
#include "utils/screen_info.h"
#include "utils/calculations.h"
#include "objects/bullet.h"
#include "objects/button.h"
//NOTE: All of the above are used

namespace SpaceShip
{
	static Text::Text ammoCount;

	static void FollowMouse(SpaceShip& ship)
	{
		Vector2 mousePos = GetMousePosition();

		ship.dir = Vector2Subtract(mousePos, ship.collisionShape.pos);

		//tanf returns result in radians
		ship.angle = atan(ship.dir.y / ship.dir.x);

		//I turn it into DEG so it's compatible with raylib functions
		ship.angle *= 180.0f / PI;

		Rotate::Quadrants myQuadrant = Rotate::GetQuadrant(ship.dir);

		if (myQuadrant != Rotate::Q1)
			FixTanValue(ship.angle, myQuadrant);
	}

	static void MovePos(SpaceShip& ship)
	{
		ship.collisionShape.pos.x += ship.speed.x* GetFrameTime(); //* GetFrameTime();
		ship.collisionShape.pos.y += ship.speed.y* GetFrameTime(); //* GetFrameTime();
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
				mag = sqrt(pow(ship.speed.x, 2.0f) + pow(ship.speed.y, 2.0f));

				ship.speed.x /= mag;
				ship.speed.y /= mag;

				ship.speed.x *= ship.maxSpeed;
				ship.speed.y *= ship.maxSpeed;

				cout << sqrt(pow(ship.speed.x, 2.0f) + pow(ship.speed.y, 2.0f)) << endl;
			}

			ship.speed.x += ship.acceleration  * normalizedDir.x;
			ship.speed.y += ship.acceleration  * normalizedDir.y;

		}

		MovePos(ship);
	}

	static void UpdateSpritePos(SpaceShip& ship)
	{
		ship.sprite.dest.x = ship.collisionShape.pos.x; //- ship.sprite.texture.width / 2;
		ship.sprite.dest.y = ship.collisionShape.pos.y; //- ship.sprite.texture.height / 2;
	}

	static void Reload(SpaceShip& ship)
	{
		for (int i = 0; i < maxAmmo; i++)
		{
			ship.bullets[i] = Bullet::GetBullet();
			Bullet::SetPos(ship.sprite.dest.x + ship.sprite.texture.width / 2, ship.sprite.dest.y, ship.bullets[i]);
		}
	}

	static void DrawBullets(SpaceShip& ship)
	{
		for (int i = 0; i < maxAmmo; i++)
			if (ship.bullets[i].isVisible)
				Bullet::Draw(ship.bullets[i]);


	}

	static bool EmptyAmmo(SpaceShip ship)
	{
		for (int i = 0; i < maxAmmo; i++)
			if (ship.bullets[i].isStored)
				return false;
		
		return true;
	}

	static int GetCurrentAmmo(SpaceShip ship)
	{
		int count = 0;
		for (int i = 0; i < maxAmmo; i++)
		{
			if (ship.bullets[i].isStored)
				count++;
		}

		return count;
	}

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

	static void Shoot(SpaceShip& ship)
	{
		Bullet::Bullet* lastBullet = &ship.bullets[maxAmmo - 1];

		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
		{
			if (!EmptyAmmo(ship))
			{
				for (int i = maxAmmo - 1; i >= 0; i--)
					if (ship.bullets[i].isStored)
					{
						lastBullet = &ship.bullets[i];
						break;
					}

				Bullet::SetPos(ship.sprite.dest.x + ship.sprite.texture.width / 2, ship.sprite.dest.y, *lastBullet);
				Bullet::Shoot(*lastBullet);
			}
			else
				//a click to reload
				Reload(ship);

			//cout << GetCurrentAmmo(ship) << endl;
		}
	}

	static void MoveBullets(SpaceShip& ship)
	{
		for (int i = 0; i < maxAmmo; i++)
			if (ship.bullets[i].isVisible)
				Bullet::Update(ship.bullets[i]);

	}

	static void InitAmmoText()
	{
		ammoCount = Text::GetText(0, 0, Text::Fonts::Default, static_cast<int>(Text::FontSize::medium), "%02i", YELLOW, RED);
		ammoCount.location.x = static_cast<int>(Text::Padding::tiny);
		ammoCount.location.y = screenHeight - Text::GetTextHeight(ammoCount);
	}

	static void UpdateAmmoText(SpaceShip ship)
	{
		if (!EmptyAmmo(ship))
			ammoCount.currentColor = YELLOW;
		else
			ammoCount.currentColor = RED;

	}

	static void DrawAmmoCount(SpaceShip ship)
	{
		Text::DrawText(ammoCount, GetCurrentAmmo(ship));
	}

	bool IsAlive(SpaceShip ship)
	{
		return ship.lives > 0;
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
		ship.lives = 6;
		ship.won = false;

		Rectangle sourceRect{};

		sourceRect.x = 0;
		sourceRect.y = 0;

		ship.sprite.source = sourceRect;

		Rectangle destRect{};

		destRect.x = screenWidth / 2;
		destRect.y = screenHeight / 2;

		ship.sprite.dest = destRect;

		Vector2 origin{};

		ship.sprite.origin = origin;

		Reload(ship);

		InitAmmoText();

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

		ship.collisionShape.radius = static_cast<int>(ship.sprite.dest.width) / 4;
	}
	void Update(SpaceShip& ship)
	{
		FollowMouse(ship);

		MoveShip(ship);

		Shoot(ship);

		MoveBullets(ship);

		ScreenWrapCheck(ship);

		UpdateSpritePos(ship);

		UpdateAmmoText(ship);
	}

	void Draw(SpaceShip ship)
	{
		DrawTexturePro(ship.sprite.texture, ship.sprite.source, ship.sprite.dest, ship.sprite.origin, ship.angle, WHITE);

		DrawAmmoCount(ship);

		DrawBullets(ship);

		DrawCircle(static_cast<int>(ship.collisionShape.pos.x), static_cast<int>(ship.collisionShape.pos.y), static_cast<float>(ship.collisionShape.radius), BLUE);
	}
}
