#include "Scene_Manager.h"

static SceneManager::GameMode currentGameMode = SceneManager::localMultiplayer;
static SceneManager::Scene currentScene = SceneManager::Menu;

void SceneManager::SetCurrentScene(Scene scene)
{
	currentScene = scene;
}

SceneManager::Scene SceneManager::GetCurrentScene()
{
	return currentScene;
}

void SceneManager::SetCurrentGameMode(GameMode mode)
{
	currentGameMode = mode;
}

SceneManager::GameMode SceneManager::GetCurrentGameMode()
{
	return currentGameMode;
}