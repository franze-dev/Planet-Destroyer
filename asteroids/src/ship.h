#pragma once
#include "raylib.h"

#include "texture_manager.h"

namespace SpaceShip
{
	struct CollisionBall
	{
		Vector2 pos;
		int radius;
	};

	struct SpaceShip
	{
		CollisionBall collisionShape;
		TextureManager::Sprite sprite;
		Vector2 modifiableSpeed;
		float maxSpeed;
		float speedIncrease;
		float angle;
		int scale;
	};

	SpaceShip GetShip();

	void SaveTexture(Texture2D texture, SpaceShip& ship);

	void Update(SpaceShip& ship);

	void Draw(SpaceShip ship);

	void FollowMouse(SpaceShip& ship);
}

