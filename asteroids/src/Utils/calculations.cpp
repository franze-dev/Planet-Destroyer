#include "utils/calculations.h"

namespace Rotate
{
	Quadrants GetQuadrant(Vector2 dir)
	{
		if (dir.y > 0 && dir.x > 0)
			return Q1;
		else if (dir.x < 0 && dir.y > 0)
			return Q2;
		else if (dir.x < 0 && dir.y < 0)
			return Q3;
		else if (dir.x > 0 && dir.y < 0)
			return Q4;

		return Q1;
	}

	void FixTanValue(float& angle, Quadrants quadrant)
	{
		switch (quadrant)
		{
		case Q2:
		case Q3:
			angle += 180;
			break;
		case Q4:
			angle += 360;
			break;
		default:
			break;
		}
	}
}

