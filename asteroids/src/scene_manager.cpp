#include "Scene_Manager.h"

namespace SceneManager
{
	static Scene currentScene = Gameplay;

	void SetCurrentScene(Scene scene)
	{
		currentScene = scene;
	}

	Scene GetCurrentScene()
	{
		return currentScene;
	}
}

