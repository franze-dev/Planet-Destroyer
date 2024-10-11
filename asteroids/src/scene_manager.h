#pragma once

namespace SceneManager
{
	//Saves every scene in the game
	enum Scene
	{
		None,
		Menu,
		Gameplay,
		Result,
	};

	//saves the gamemodes
	enum GameMode
	{
		localMultiplayer,
		singlePlayer
	};

	//changes the current scene
	void SetCurrentScene(Scene scene);
	//returns the current scene
	Scene GetCurrentScene();

}

