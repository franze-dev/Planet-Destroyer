#include "bullet.h"

namespace Bullet
{
	Bullet GetBullet()
	{
		Bullet bullet{};

		bullet.rect.height = 16;
		bullet.rect.width = bullet.rect.height/2;

		return bullet;
	}

	void SetPos(float x, float y, Bullet& bullet)
	{
		bullet.rect.x = x;
		bullet.rect.y = y;
	}

	void Draw(Bullet bullet)
	{
		DrawRectangle(static_cast<int>(bullet.rect.x), static_cast<int>(bullet.rect.y), static_cast<int>(bullet.rect.width), static_cast<int>(bullet.rect.height), MAGENTA);
	}
	
	/*void Update(Bullet& bullet)
	{
		return;
	}*/
}
