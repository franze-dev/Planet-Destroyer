#include "result_scene.h"

#include "raylib.h"

#include "button.h"
#include "scene_manager.h"
//NOTE: All of the above are used

static Button::Button backToMenuButton;
static Button::Button exitButton;

static int buttonsPadding = 20;
static int defaultFontSize = 40;

void ResultScene::Init()
{
	backToMenuButton.shape.x = static_cast<float>(GetScreenWidth()) * 3 / 8;
	backToMenuButton.shape.y = static_cast<float>(GetScreenHeight()) * 5 / 8;
	backToMenuButton.shape.width = 150.0f;
	backToMenuButton.shape.height = 30.0f;
	backToMenuButton.textShown.content = "BACK TO MENU";
	backToMenuButton.defaultColor = DARKGRAY;
	backToMenuButton.currentColor = backToMenuButton.defaultColor;
	backToMenuButton.highlightColor = BLUE;

	exitButton = backToMenuButton;
	exitButton.shape.y += exitButton.shape.height + buttonsPadding;
	exitButton.textShown.content = "EXIT";
	exitButton.highlightColor = RED;
}

void ResultScene::Update()
{
	if (IsMouseOnButton(backToMenuButton))
	{
		backToMenuButton.currentColor = backToMenuButton.highlightColor;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			SceneManager::SetCurrentScene(SceneManager::Menu);
	}
	else
		backToMenuButton.currentColor = backToMenuButton.defaultColor;

	if (IsMouseOnButton(exitButton))
	{
		exitButton.currentColor = exitButton.highlightColor;

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			SceneManager::SetCurrentScene(SceneManager::None);
	}
	else
		exitButton.currentColor = exitButton.defaultColor;
}

void ResultScene::Draw()
{

}
