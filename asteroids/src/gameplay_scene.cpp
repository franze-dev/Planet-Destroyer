#include "gameplay_scene.h"

#include "raylib.h"

#include "ship.h"

namespace Gameplay
{
	SpaceShip::SpaceShip ship;
	static Texture2D shipTexture;

	void LoadTextures()
	{
		shipTexture = LoadTexture("res/sprites/spaceship.png");
	}

	void UnloadTextures()
	{
		UnloadTexture(shipTexture);
	}

	void Init()
	{
		ship = SpaceShip::GetShip();
		SpaceShip::SaveTexture(shipTexture, ship);
	}

	void Update()
	{
		SpaceShip::Update(ship);
	}

	void Draw()
	{
		SpaceShip::Draw(ship);
	}
}


