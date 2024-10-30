#pragma once

#include "raylib.h"

#include "objects/ship.h"
#include "utils/calculations.h"
#include "utils/texture_manager.h"

namespace Planet
{
	const int startPlanets = 25;
	const int maxPossiblePlanets = startPlanets * 9;

	struct Planet
	{
		float maxSpeed;
		int scale;
		int damage;
		int size;

		float angle;
	
		bool visible;
		bool isSmaller;
		bool isSpecial;
		Collide::CollisionBall collisionShape;
		TextureManager::Sprite sprite;
		Vector2 speed;
		Vector2 dir;
	};

	void DividePlanet(Planet& planet, Planet planets[]);
	void LoadTextures();
	void UnloadTextures();
	void Init(Planet planets[]);
	void Update(SpaceShip::SpaceShip& ship, Planet planets[]);
	void Draw(Planet planets[]);
	void DeletePlanet(Planet& planet);
}