#include "PauseMenu.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "raylib.h"

UIManager::Text pauseTitle;
UIManager::Button continueButton;
UIManager::Button backToMenuButton;

int defaultFontSize = 40;
int buttonsPadding = 30;

void PauseMenu::Init()
{
#pragma region PAUSE_TITLE
	pauseTitle.color = YELLOW;
	pauseTitle.content = "PAUSED";
	pauseTitle.fontSize = defaultFontSize;
	pauseTitle.location.x = GetScreenWidth() * 2/8 - MeasureText(pauseTitle.content.data(), pauseTitle.fontSize) / 2;
	pauseTitle.location.y = GetScreenHeight() / 2 + pauseTitle.fontSize / 2;
#pragma endregion

#pragma region CONTINUE_BUTTON
	continueButton.defaultColor = DARKGRAY;
	continueButton.currentColor = DARKGRAY;
	continueButton.highlightColor = YELLOW;
	continueButton.shape.width = MeasureText(pauseTitle.content.data(), pauseTitle.fontSize);
	continueButton.shape.height = defaultFontSize;
	continueButton.shape.x = GetScreenWidth() * 5 / 8;
	continueButton.shape.y = pauseTitle.location.y - continueButton.shape.height + buttonsPadding;
	continueButton.textShown = "CONTINUE";

#pragma endregion

#pragma region BACKTOMENU_BUTTON
	backToMenuButton = continueButton;
	backToMenuButton.shape.y += buttonsPadding + continueButton.shape.height;
	backToMenuButton.highlightColor = BLUE;
	backToMenuButton.textShown = "BACK TO MENU";

#pragma endregion


}

void PauseMenu::Update(BallSpace::Ball& ball)
{
	if (UIManager::IsMouseOnButton(continueButton))
	{
		continueButton.currentColor = continueButton.highlightColor;
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			ball.paused = false;
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
	DrawText(pauseTitle.content.data(), pauseTitle.location.x, pauseTitle.location.y, pauseTitle.fontSize, pauseTitle.color);
	
	UIManager::DrawButtonRect(continueButton);
	UIManager::DrawButtonRect(backToMenuButton);
	UIManager::DrawButtonText(continueButton, WHITE, defaultFontSize/2);
	UIManager::DrawButtonText(backToMenuButton, WHITE, defaultFontSize/2);
}