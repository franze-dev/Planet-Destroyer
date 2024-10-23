#pragma once

#include "raylib.h"
#include "calculations.h"
#include "texture_manager.h"

namespace Planet
{
	struct PlanetPart
	{
		float maxSpeed;
		Vector2 speed;
		Vector2 dir;
		Collide::CollisionBall collisionShape;
		TextureManager::Sprite sprite;
		bool isAlive;
	};

	struct Planet
	{
		float maxSpeed;
		int scale;
		int damage;
		int lives;
		
		//I need to have these two separately so I can use the two parts sprites at the same time.
		int width;
		int height;

		int angle1;
		int angle2;
	
		bool isComplete;
		Collide::CollisionBall collisionShape;
		Vector2 speed;
		Vector2 dir;
		PlanetPart part1;
		PlanetPart part2;
	};

	void LoadTextures();
	void UnloadTextures();
	void Init();
	void Update();
	void Draw();
}