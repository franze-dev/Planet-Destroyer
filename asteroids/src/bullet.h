#pragma once
#include "raylib.h"

#include "ship.h"

namespace Bullet
{
	struct Bullet
	{
		Rectangle rect;
		Vector2 speed;
		Vector2 dir;
		float damage;
		bool isAlive;
	};

	Bullet GetBullet();
	void SetPos(float x, float y, Bullet& bullet);
	void Draw(Bullet bullet);
	//void Update(Bullet& bullet);

}