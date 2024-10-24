#include "gameplay_scene.h"

#include "raylib.h"

#include "ship.h"
#include "planet.h"

namespace Gameplay
{
	SpaceShip::SpaceShip ship;
	static Texture2D shipTexture;

	void LoadTextures()
	{
		shipTexture = LoadTexture("res/sprites/spaceship.png");
		Planet::LoadTextures();
	}

	void UnloadTextures()
	{
		UnloadTexture(shipTexture);
		Planet::UnloadTextures();
	}

	void Init()
	{
		ship = SpaceShip::GetShip();
		SpaceShip::SaveTexture(shipTexture, ship);
		Planet::Init();
	}

	void Update()
	{
		SpaceShip::Update(ship);
		Planet::Update(ship);
	}

	void Draw()
	{
		SpaceShip::Draw(ship);
		Planet::Draw();
	}
}


