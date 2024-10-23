#pragma once

#include "raylib.h"
#include "calculations.h"
#include "texture_manager.h"

namespace Planet
{
	struct Planet
	{
		float maxSpeed;
		int scale;
		int damage;
		bool isSparePart;
		Collide::CollisionBall collisionShape;
		TextureManager::Sprite sprite;
		Vector2 speed;
		Vector2 dir;
	};

	Planet GetPlanet();
	void SaveTexture(Texture2D texture, Planet& planet);
	void Draw(Planet planet);
	void MovePlanet(Vector2 normalizedDir, Planet& planet);
	void Update();
}