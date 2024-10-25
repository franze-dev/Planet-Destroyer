#pragma once
#include "raylib.h"

namespace Bullet
{
	struct Bullet
	{
		Rectangle rect;
		Vector2 speed;
		Vector2 dir;
		float maxSpeed;
		float angle;
		float damage;
		bool isStored;
		bool isVisible;
	};

	Bullet GetBullet();
	void SetPos(float x, float y, Bullet& bullet);
	void Shoot(Bullet& bullet);
	void Draw(Bullet bullet);
	void Update(Bullet& bullet);

}