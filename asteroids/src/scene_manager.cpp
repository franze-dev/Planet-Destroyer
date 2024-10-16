#include "Scene_Manager.h"

namespace SceneManager
{
	static Scene currentScene = Menu;

	void SetCurrentScene(Scene scene)
	{
		currentScene = scene;
	}

	Scene GetCurrentScene()
	{
		return currentScene;
	}
}

