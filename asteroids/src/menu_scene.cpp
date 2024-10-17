#include "menu_scene.h"

#include "raylib.h"

#include <iostream>
#include <string>

#include "Scene_Manager.h"
#include "UI_Manager.h"
#include "constants.h"

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
	exitButton.shape.y += static_cast<int>(UIManager::Padding::medium);
	exitButton.highlightColor = RED;
#pragma endregion

#pragma region TITLE_TEXTS

	titlePart1 = UIManager::GetText(0, 0, UIManager::Fonts::Title1, static_cast<int>(UIManager::FontSize::big), "PLANET", MAGENTA);
	titlePart1.location.x = static_cast<float>(screenWidth) / 2.0f - UIManager::GetTextWidth(titlePart1)/2.0f;
	titlePart1.location.y = static_cast<float>(UIManager::Padding::medium);
	titlePart2 = UIManager::GetText(0, titlePart1.location.y + UIManager::GetTextHeight(titlePart1) + static_cast<float>(UIManager::Padding::small), UIManager::Fonts::Title2, static_cast<int>(UIManager::FontSize::big2), "DESTROYER", YELLOW);
	titlePart2.location.x = static_cast<float>(screenWidth) / 2.0f - UIManager::GetTextWidth(titlePart2) / 2.0f;

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

	/*DrawButtonRect(playButton);
	DrawButtonRect(exitButton);
	DrawButtonRect(gameModeButton);*/

	/*DrawButtonText(playButton, WHITE, defaultFontSize / 2);
	DrawButtonText(exitButton, WHITE, defaultFontSize / 2);
	DrawButtonText(gameModeButton, WHITE, defaultFontSize / 2);*/
}
