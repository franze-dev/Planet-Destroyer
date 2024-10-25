#pragma once

#include "raylib.h"

#include "ship.h"
#include "calculations.h"
#include "texture_manager.h"

namespace Planet
{
	struct Planet
	{
		float maxSpeed;
		int scale;
		int damage;
		int lives;

		int angle;
	
		bool isSmaller;
		Collide::CollisionBall collisionShape;
		TextureManager::Sprite sprite;
		Vector2 speed;
		Vector2 dir;
	};

	void LoadTextures();
	void UnloadTextures();
	void Init();
	void Update(SpaceShip::SpaceShip& ship);
	void Draw();
}