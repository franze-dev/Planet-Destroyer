#include "raylib.h"
#include "ResultScene.h"
#include "UIManager.h"
#include "SceneManager.h"

static Players::Player savedPlayer1;
static Players::Player savedPlayer2;
static UIManager::Button backToMenuButton;
static UIManager::Button exitButton;

static int buttonsPadding = 20;
static int smallerFontSize = 15;
static int defaultFontSize = 40;

void ResultScene::SavePlayers(Players::Player player1, Players::Player player2)
{
	savedPlayer1 = player1;
	savedPlayer2 = player2;
}

void ResultScene::Init()
{
	backToMenuButton.shape.x = GetScreenWidth() * 3 / 8;
	backToMenuButton.shape.y = GetScreenHeight() * 5 / 8;
	backToMenuButton.shape.width = 150;
	backToMenuButton.shape.height = 30;
	backToMenuButton.textShown = "BACK TO MENU";
	backToMenuButton.defaultColor = DARKGRAY;
	backToMenuButton.currentColor = backToMenuButton.defaultColor;
	backToMenuButton.highlightColor = BLUE;

	exitButton = backToMenuButton;
	exitButton.shape.y += exitButton.shape.height + buttonsPadding;
	exitButton.textShown = "EXIT";
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
	string winner = " ";

	DrawText(TextFormat("%02i", savedPlayer1.score), GetScreenWidth() * 3 / 8, GetScreenHeight() * 1 / 8, defaultFontSize, RED); // PLAYER 1
	DrawText(TextFormat("%02i", savedPlayer2.score), GetScreenWidth() * 4 / 8, GetScreenHeight() * 1 / 8, defaultFontSize, RED); // PLAYER 2
	DrawText(savedPlayer1.name.data(), GetScreenWidth() * 3 / 8, 10, defaultFontSize, WHITE);
	DrawText(savedPlayer2.name.data(), GetScreenWidth() * 4 / 8, 10, defaultFontSize, WHITE);

	if (savedPlayer1.score > savedPlayer2.score)
		winner = savedPlayer1.name;
	else
		winner = savedPlayer2.name;

	winner += " has won!";

	DrawText(winner.data(), GetScreenWidth() / 2 - MeasureText(winner.data(), defaultFontSize) / 2, GetScreenHeight() * 3 / 8, defaultFontSize, YELLOW);

	DrawButtonRect(backToMenuButton);
	DrawButtonText(backToMenuButton, WHITE, smallerFontSize);

	DrawButtonRect(exitButton);
	DrawButtonText(exitButton, WHITE, smallerFontSize);
}
