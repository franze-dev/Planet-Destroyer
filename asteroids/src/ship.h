#pragma once
#include "raylib.h"

#include "texture_manager.h"
#include "bullet.h"

namespace SpaceShip
{
	const int maxAmmo = 50;

	struct CollisionBall
	{
		Vector2 pos;
		int radius;
	};

	struct SpaceShip
	{
		float maxSpeed;
		float acceleration;
		float angle;
		int scale;
		CollisionBall collisionShape;
		TextureManager::Sprite sprite;
		Vector2 speed;
		Vector2 dir;
		Bullet::Bullet bullets[maxAmmo];
	};

	SpaceShip GetShip();

	void SaveTexture(Texture2D texture, SpaceShip& ship);

	void Update(SpaceShip& ship);

	void Draw(SpaceShip ship);

	
}

