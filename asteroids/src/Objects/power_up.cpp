#include "objects/power_up.h"

#include "raylib.h"

#include "objects//text.h"
#include "utils/screen_info.h"

namespace PowerUp
{
	static const int planetsToShoot = 10;
	static int planetsShot = 0;

	PowerUp myPower;

	Text::Text powerActive;

	static void GrabPower(SpaceShip::SpaceShip& ship)
	{
		myPower.visible = false;
		myPower.active = true;
		for (int i = 0; i < SpaceShip::maxAmmo; i++)
		{
			if (ship.bullets[i].isStored)
			{
				cout << "powered!" << endl;

				ship.bullets[i].powered = true;
			}
		}
	}

	static void ShipCollisionCheck(SpaceShip::SpaceShip& ship)
	{
		float distX = ship.collisionShape.pos.x - myPower.collisionShape.pos.x;
		float distY = ship.collisionShape.pos.y - myPower.collisionShape.pos.y;

		float distance = sqrt((distX * distX) + (distY * distY));

		if (distance <= ship.collisionShape.radius + myPower.collisionShape.radius)
		{
			GrabPower(ship);
		}
	}

	static void CheckPowerSpawn()
	{
		if (planetsShot == planetsToShoot)
		{
			if (!myPower.visible)
			{
				myPower.collisionShape.pos.x = static_cast<float>(GetRandomValue(0, screenWidth));
				myPower.collisionShape.pos.y = static_cast<float>(GetRandomValue(0, screenHeight));

				myPower.visible = true;
				planetsShot = 0;
			}
			else if (!myPower.active)
			{
				planetsShot = 0;
			}
		}
	}

	static void CheckPowerActive(SpaceShip::SpaceShip ship)
	{
		if (planetsShot == planetsToShoot && myPower.active)
		{
			myPower.active = false;
			for (int i = 0; i < SpaceShip::maxAmmo; i++)
			{
				if (ship.bullets[i].powered)
				{
					ship.bullets[i].powered = false;
				}
			}
			planetsShot = 0;
		}
	}

	void IncreasePlanetsShot()
	{
		planetsShot++;
	}

	void Init()
	{
		powerActive = Text::GetText(screenWidth / 2, 0, Text::Fonts::Title2, static_cast<int>(Text::FontSize::big), "POWER ACTIVE", WHITE);
		Text::CenterTextX(powerActive);
		powerActive.location.y = screenHeight - Text::GetTextHeight(powerActive);
		planetsShot = 0;
		myPower.collisionShape.radius = 10;
		myPower.active = false;
		myPower.visible = false;
	}

	void Update(SpaceShip::SpaceShip& ship)
	{
		CheckPowerSpawn();
		ShipCollisionCheck(ship);
		CheckPowerActive(ship);
	}

	void Draw()
	{
		int maxColors = 2;
		int randomColor = GetRandomValue(0, maxColors);
		Color color = BLACK;

		switch (randomColor)
		{
		case 0:
			color = YELLOW;
			break;
		case 1:
			color = SKYBLUE;
			break;
		case 2:
			color = MAGENTA;
			break;

		default:
			break;
		}

		if (myPower.visible)
			DrawCircle(static_cast<int>(myPower.collisionShape.pos.x), static_cast<int>(myPower.collisionShape.pos.y), static_cast<float>(myPower.collisionShape.radius), color);

		if (myPower.active)
		{
			powerActive.currentColor = color;
			Text::DrawText(powerActive);
		}
	}
}


