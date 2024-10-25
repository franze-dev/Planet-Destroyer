#pragma once
#include "raylib.h"

#include "utils/texture_manager.h"
#include "utils/calculations.h"
#include "objects/bullet.h"

namespace SpaceShip
{
	const int maxAmmo = 50;

	struct SpaceShip
	{
		float maxSpeed;
		float acceleration;
		float angle;
		int scale;
		int lives;
		bool won;
		Collide::CollisionBall collisionShape;
		TextureManager::Sprite sprite;
		Bullet::Bullet bullets[maxAmmo];
		Vector2 speed;
		Vector2 dir;
	};

	bool IsAlive(SpaceShip ship);

	SpaceShip GetShip();

	void SaveTexture(Texture2D texture, SpaceShip& ship);

	void Update(SpaceShip& ship);

	void Draw(SpaceShip ship);

	
}

