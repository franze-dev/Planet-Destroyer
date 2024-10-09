#include "menu.h"
#include <iostream>
#include <string>
#include "raylib.h"
#include "Scene_Manager.h"
#include "UI_Manager.h"
using namespace std;

enum Options
{
	Play,
	Exit
};

static UIManager::Button playButton;
static UIManager::Button exitButton;
static UIManager::Button gameModeButton;

static UIManager::Text titlePart1;
static UIManager::Text titlePart2;
static UIManager::Text titlePart3;

static short defaultFontSize = 40;
//space between buttons
static short buttonsPadding = 60;

void MenuScene::Init()
{
#pragma region PLAY_BUTTON
	playButton.textShown.content = "PLAY";
	playButton.shape.width = 150;
	playButton.shape.height = 30;
	playButton.shape.x = static_cast<float>(GetScreenWidth()) / 2.0f - playButton.shape.width / 2.0f;
	playButton.shape.y = static_cast<float>(GetScreenHeight()) / 2.0f - playButton.shape.height / 2.0f;
	playButton.defaultColor = DARKGRAY;
	playButton.currentColor = playButton.defaultColor;
	playButton.highlightColor = YELLOW;
#pragma endregion

#pragma region EXIT_BUTTON
	exitButton = playButton;
	exitButton.textShown.content = "EXIT";
	exitButton.shape.y += buttonsPadding;
	exitButton.highlightColor = RED;
#pragma endregion

#pragma region TITLE_TEXTS
	
#pragma endregion
}

void MenuScene::Update()
{
	if (IsMouseOnButton(playButton))
	{
		playButton.currentColor = playButton.highlightColor;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			SceneManager::SetCurrentScene(SceneManager::Gameplay);
	}
	else
		playButton.currentColor = playButton.defaultColor;


	if (IsMouseOnButton(exitButton))
	{
		exitButton.currentColor = exitButton.highlightColor;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			SceneManager::SetCurrentScene(SceneManager::None);
	}
	else
		exitButton.currentColor = exitButton.defaultColor;

}

void MenuScene::Draw()
{
	PrintText(titlePart1);
	PrintText(titlePart2);
	PrintText(titlePart3);

	DrawButtonRect(playButton);
	DrawButtonRect(exitButton);
	DrawButtonRect(gameModeButton);

	DrawButtonText(playButton, WHITE, defaultFontSize / 2);
	DrawButtonText(exitButton, WHITE, defaultFontSize / 2);
	DrawButtonText(gameModeButton, WHITE, defaultFontSize / 2);
}
