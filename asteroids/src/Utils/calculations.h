#pragma once

#include "raylib.h"

namespace Collide
{
	struct CollisionBall
	{
		Vector2 pos;
		int radius;
	};

	//To calculate the distance between the bullets and the planets
	struct Distances
	{
		int pinPointX;
		int pinPointY;
		int distX;
		int distY;
		int distance;
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
