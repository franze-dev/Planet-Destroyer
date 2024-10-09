#include "gameplay.h"

// Notes:
// left click > shoot
// right click > increase speed
// NEEDS A SPEED LIMIT
// SPEED NEVER DECREASES
// BULLET COOLDOWN
// DO NOT USE NEGATIVE VALUES. To get a "negative" angle, do 360 - angle to get that angle.

// CARTESIANAS (x, y)
// POLARES: (radio, angulo)

// SOH CAH TOA (estudia)
// USAR FUNCION DE RAYLIB PARA DARLE EL ANGULO CORRESPONDIENTE

int main()
{
	Gameplay::Play();
}