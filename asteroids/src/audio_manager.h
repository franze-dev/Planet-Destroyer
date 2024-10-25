#pragma once
#include <iostream>
#include "raylib.h"

using namespace std;

namespace Audio
{
	enum class Song
	{
		menu,
		gameplay
	};

	enum class ButtonSfx
	{
		sfx0,
		sfx1,
		sfx2,
		sfx3,
	};

	enum class Sfx
	{
		shoot,
		planet
	};

	void Play(Song song);

	void Play(Sfx sound);

	void Update(Song song);

	void Load();

	Music GetMusic(Song song);

	Sound GetSound(Sfx sound);

	Sound GetSound(ButtonSfx sound);

	void UnLoad();
}