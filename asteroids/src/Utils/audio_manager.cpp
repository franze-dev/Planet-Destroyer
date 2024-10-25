#include "utils/audio_manager.h"

namespace Audio
{
#pragma region DIRECTORIES
	//music
	static string menuMusicDir = "res/sound/music/alien invasion.mp3";
	static string gameplayMusicDir = "res/sound/music/galactic fury.mp3";

	//button sfx
	static string buttonSfx0Dir = "res/sound/sfx/forceField_000.ogg";
	static string buttonSfx1Dir = "res/sound/sfx/forceField_001.ogg";
	static string buttonSfx2Dir = "res/sound/sfx/forceField_002.ogg";
	static string buttonSfx3Dir = "res/sound/sfx/forceField_003.ogg";

	//shoot sfx
	static string shootSfxDir = "res/sound/sfx/laserRetro_000.ogg";

	//planet explosion
	static string planetSfxDir = "res/sound/sfx/lowFrequency_explosion_000.ogg";
#pragma endregion

	//music
	static Music menuMusic;
	static Music gameplayMusic;

	//button sfx
	static Sound buttonSfx0;
	static Sound buttonSfx1;
	static Sound buttonSfx2;
	static Sound buttonSfx3;

	//shoot sfx
	static Sound shootSfx;

	//planet explosion
	static Sound planetSfx;

	ButtonSfx GetRandomSfx()
	{
		ButtonSfx sfx = static_cast<ButtonSfx>(GetRandomValue(0, static_cast<int>(ButtonSfx::sfx3) + 1));

		return sfx;
	}

	void Play(Song song)
	{
		PlayMusicStream(GetMusic(song));
	}

	void Play(Sfx sound)
	{
		PlaySound(GetSound(sound));
	}

	void Play(ButtonSfx sound)
	{
		PlaySound(GetSound(sound));
	}

	void Update(Song song)
	{
		UpdateMusicStream(GetMusic(song));
	}

	void Stop(Song song)
	{
		StopMusicStream(GetMusic(song));
	}

	bool IsPlaying(Sfx sfx)
	{
		return IsSoundPlaying(GetSound(sfx));
	}

	bool IsPlaying(ButtonSfx sfx)
	{
		return IsSoundPlaying(GetSound(sfx));
	}

	bool IsPlaying(Song song)
	{
		return IsMusicStreamPlaying(GetMusic(song));
	}

	void Load()
	{
		InitAudioDevice();

		menuMusic = LoadMusicStream(menuMusicDir.data());
		gameplayMusic = LoadMusicStream(gameplayMusicDir.data());

		buttonSfx0 = LoadSound(buttonSfx0Dir.data());
		buttonSfx1 = LoadSound(buttonSfx1Dir.data());
		buttonSfx2 = LoadSound(buttonSfx2Dir.data());
		buttonSfx3 = LoadSound(buttonSfx3Dir.data());

		shootSfx = LoadSound(shootSfxDir.data());
		planetSfx = LoadSound(planetSfxDir.data());
	}

	Music GetMusic(Song song)
	{
		switch (song)
		{
		case Song::menu:
			return menuMusic;
			break;
		case Song::gameplay:
			return gameplayMusic;
			break;
		default:
			return menuMusic;
			break;
		}
	}

	Sound GetSound(Sfx sound)
	{
		switch (sound)
		{
		case Sfx::shoot:
			return shootSfx;
			break;
		case Sfx::planet:
			return planetSfx;
			break;
		default:
			return shootSfx;
			break;
		}
	}

	Sound GetSound(ButtonSfx sound)
	{
		switch (sound)
		{
		case ButtonSfx::sfx0:
			return buttonSfx0;
			break;
		case ButtonSfx::sfx1:
			return buttonSfx1;
			break;
		case ButtonSfx::sfx2:
			return buttonSfx2;
			break;
		case ButtonSfx::sfx3:
			return buttonSfx3;
			break;
		default:
			return buttonSfx0;
			break;
		}
	}

	void UnLoad()
	{
		UnloadMusicStream(menuMusic);
		UnloadMusicStream(gameplayMusic);

		UnloadSound(buttonSfx0);
		UnloadSound(buttonSfx1);
		UnloadSound(buttonSfx2);
		UnloadSound(buttonSfx3);

		UnloadSound(shootSfx);
		UnloadSound(planetSfx);

		CloseAudioDevice();
	}
}