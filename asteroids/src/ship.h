#pragma once
#include "raylib.h"

#include "texture_manager.h"
#include "calculations.h"
#include "bullet.h"

namespace SpaceShip
{
	const int maxAmmo = 50;

	struct SpaceShip
	{
		float maxSpeed;
		float acceleration;
		float angle;
		int scale;
		Collide::CollisionBall collisionShape;
		TextureManager::Sprite sprite;
		Bullet::Bullet bullets[maxAmmo];
		Vector2 speed;
		Vector2 dir;
	};

	SpaceShip GetShip();

	void SaveTexture(Texture2D texture, SpaceShip& ship);

	void Update(SpaceShip& ship);

	void Draw(SpaceShip ship);

	
}

