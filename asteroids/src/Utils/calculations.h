#pragma once

#include "raylib.h"

namespace Collide
{
	struct CollisionBall
	{
		Vector2 pos;
		int radius;
	};
}

namespace Rotate
{
	enum Quadrants
	{
		Q1,
		Q2,
		Q3,
		Q4
	};

	Quadrants GetQuadrant(Vector2 dir);
	void FixTanValue(float& angle, Quadrants quadrant);
}
