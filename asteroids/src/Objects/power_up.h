#pragma once

#include "utils/calculations.h"
#include "objects/ship.h"
#include "objects/planet.h"

namespace PowerUp
{
	struct PowerUp
	{
		bool visible;

		bool active;
		int angle;
		Collide::CollisionBall collisionShape;
		Vector2 dir;
	};

	void IncreasePlanetsShot();

	void Init();
	void Update(SpaceShip::SpaceShip& ship, Planet::Planet planets[]);
	void Draw();
}

