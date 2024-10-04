#pragma once
#include "Player.h"

namespace ResultScene
{
	void Init();
	void Update();
	void Draw();
	//When the game ends, I need the players to show the results. To prevent them from disappearing, I save them in here.
	void SavePlayers(Players::Player player1, Players::Player player2);
}
