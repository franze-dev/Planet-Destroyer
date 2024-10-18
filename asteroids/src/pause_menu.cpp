#include "Pause_Menu.h"
#include "UI_Manager.h"
#include "Scene_Manager.h"
#include "raylib.h"

UIManager::Text pauseTitle;
UIManager::Button continueButton;
UIManager::Button backToMenuButton;

int defaultFontSize = 40;
int buttonsPadding = 30;

void PauseMenu::Init()
{
#pragma region PAUSE_TITLE
	pauseTitle.currentColor = YELLOW;
	pauseTitle.content = "PAUSED";
	pauseTitle.fontSize = defaultFontSize;
	pauseTitle.location.x = static_cast<float>(GetScreenWidth()) * 2/8 - static_cast<float>(MeasureText(pauseTitle.content.data(), pauseTitle.fontSize)) / 2.0f;
	pauseTitle.location.y = static_cast<float>(GetScreenHeight()) / 2.0f + static_cast<float>(pauseTitle.fontSize) / 2.0f;
#pragma endregion

#pragma region CONTINUE_BUTTON
	continueButton.defaultColor = DARKGRAY;
	continueButton.currentColor = DARKGRAY;
	continueButton.highlightColor = YELLOW;
	continueButton.shape.width = static_cast<float>(MeasureText(pauseTitle.content.data(), pauseTitle.fontSize));
	continueButton.shape.height = static_cast<float>(defaultFontSize);
	continueButton.shape.x = static_cast<float>(GetScreenWidth()) * 5 / 8;
	continueButton.shape.y = pauseTitle.location.y - continueButton.shape.height + static_cast<float>(buttonsPadding);
	continueButton.textShown.content = "CONTINUE";

#pragma endregion

#pragma region BACKTOMENU_BUTTON
	backToMenuButton = continueButton;
	backToMenuButton.shape.y += buttonsPadding + continueButton.shape.height;
	backToMenuButton.highlightColor = BLUE;
	backToMenuButton.textShown.content = "BACK TO MENU";

#pragma endregion


}

void PauseMenu::Update()
{
	if (UIManager::IsMouseOnButton(continueButton))
	{
		continueButton.currentColor = continueButton.highlightColor;
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			//pause!
		}
	}
	else
		continueButton.currentColor = continueButton.defaultColor;

	if (UIManager::IsMouseOnButton(backToMenuButton))
	{
		backToMenuButton.currentColor = backToMenuButton.highlightColor;
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			SceneManager::SetCurrentScene(SceneManager::Menu);
	}
	else
		backToMenuButton.currentColor = backToMenuButton.defaultColor;

}

void PauseMenu::Draw()
{
	DrawText(pauseTitle.content.data(), static_cast<int>(pauseTitle.location.x), static_cast<int>(pauseTitle.location.y), pauseTitle.fontSize, pauseTitle.currentColor);
	
	UIManager::DrawButton(continueButton);
	UIManager::DrawButton(backToMenuButton);
}