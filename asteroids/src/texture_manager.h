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


}

