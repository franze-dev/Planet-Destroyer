#pragma once
#include "Ball.h"

namespace PauseMenu
{
	void Init();
	//Needs the ball to inform that the game is paused to it.
	void Update(BallSpace::Ball& ball);
	void Draw();
}
