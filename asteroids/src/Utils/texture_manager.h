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

	const string jupiterSprite = "res/sprites/jupiter.png";

	const string marsSprite = "res/sprites/mars.png";

	const string neptuneSprite = "res/sprites/neptune.png";

	const string saturnSprite = "res/sprites/saturn.png";

	const string uranusSprite = "res/sprites/uranus.png";

	const string venusSprite = "res/sprites/venus.png";

	const string earthSprite = "res/sprites/earth.png";

	const string backgroundSprite = "res/sprites/space_bg.png";
}

