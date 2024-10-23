#pragma once
#include <iostream>

#include "raylib.h"

using namespace std;

namespace TextureManager
{
	struct Sprite
	{
		string textureDir;
		Rectangle source;
		Rectangle dest;
		Vector2 origin;
		Texture2D texture;
	};

	const string shipSprite = "res/sprites/spaceship.png";

	const string jupiterSprite1 = "res/sprites/jupiter - part1.png";
	const string jupiterSprite2 = "res/sprites/jupiter - part2.png";

	const string marsSprite1 = "res/sprites/mars - part1.png";
	const string marsSprite2 = "res/sprites/mars - part2.png";

	const string neptuneSprite1 = "res/sprites/neptune - part1.png";
	const string neptuneSprite2 = "res/sprites/neptune - part2.png";

	const string saturnSprite1 = "res/sprites/saturn - part1.png";
	const string saturnSprite2 = "res/sprites/saturn - part2.png";

	const string uranusSprite1 = "res/sprites/uranus - part1.png";
	const string uranusSprite2 = "res/sprites/uranus - part2.png";

	const string venusSprite1 = "res/sprites/venus - part1.png";
	const string venusSprite2 = "res/sprites/venus - part2.png";

	const string earthSprite1 = "res/sprites/earth - part1.png";
	const string earthSprite2 = "res/sprites/earth - part2.png";

}

