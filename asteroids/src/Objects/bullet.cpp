#include "objects/bullet.h"

#include "raymath.h"

#include "utils/calculations.h"
#include "utils/screen_info.h"

//NOTE: All of the above are used

namespace Bullet
{
	Bullet GetBullet()
	{
		Bullet bullet{};

		bullet.rect.height = 8;
		bullet.rect.width = bullet.rect.height;
		bullet.maxSpeed = 400.0f;
		bullet.speed = { bullet.maxSpeed, bullet.maxSpeed };
		bullet.isStored = true;
		bullet.isVisible = false;

		return bullet;
	}

	void SetPos(float x, float y, Bullet& bullet)
	{
		bullet.rect.x = x - bullet.rect.width / 2;
		bullet.rect.y = y;
	}

	void Shoot(Bullet& bullet)
	{
		bullet.isVisible = true;

		Vector2 mousePos = GetMousePosition();

		bullet.dir = Vector2Subtract(mousePos, { bullet.rect.x, bullet.rect.y });

		//tanf returns result in radians
		bullet.angle = static_cast<float>(atan(bullet.dir.y / bullet.dir.x));

		//I turn it into DEG so it's compatible with raylib functions
		bullet.angle *= 180.0f / PI;

		Rotate::Quadrants myQuadrant = Rotate::GetQuadrant(bullet.dir);

		if (myQuadrant != Rotate::Q1)
			Rotate::FixTanValue(bullet.angle, myQuadrant);

		bullet.isStored = false;
	}

	void Draw(Bullet bullet)
	{
		DrawRectanglePro(bullet.rect, { 0,0 }, bullet.angle, MAGENTA);
	}

	void Update(Bullet& bullet)
	{
		Vector2 normalizedDir{};

		normalizedDir.x = bullet.dir.x / static_cast<float>(sqrt(pow(bullet.dir.x, 2.0f) + pow(bullet.dir.y, 2.0f)));
		normalizedDir.y = bullet.dir.y / static_cast<float>(sqrt(pow(bullet.dir.x, 2.0f) + pow(bullet.dir.y, 2.0f)));

		bullet.rect.x += bullet.speed.x * normalizedDir.x * GetFrameTime();
		bullet.rect.y += bullet.speed.y * normalizedDir.y * GetFrameTime();

		if (bullet.rect.x > screenWidth || bullet.rect.x + bullet.rect.width < 0 || bullet.rect.y > screenHeight || bullet.rect.y + bullet.rect.height < 0)
			bullet.isVisible = false;
	}
}
