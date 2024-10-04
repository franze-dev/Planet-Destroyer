#include <iostream>
#include <string>
#include "raylib.h"
#include "MenuScene.h"
#include "SceneManager.h"
#include "UIManager.h"
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
	playButton.textShown = "PLAY";
	playButton.shape.width = 150;
	playButton.shape.height = 30;
	playButton.shape.x = GetScreenWidth() / 2 - playButton.shape.width / 2;
	playButton.shape.y = GetScreenHeight() / 2 - playButton.shape.height / 2;
	playButton.defaultColor = DARKGRAY;
	playButton.currentColor = playButton.defaultColor;
	playButton.highlightColor = YELLOW;
#pragma endregion

#pragma region EXIT_BUTTON
	exitButton = playButton;
	exitButton.textShown = "EXIT";
	exitButton.shape.y += buttonsPadding;
	exitButton.highlightColor = RED;
#pragma endregion

#pragma region GAMEMODE_SWITCH
	gameModeButton = exitButton;
	gameModeButton.textAlt1 = "GAMEMODE: LOCAL MULTIPLAYER";
	gameModeButton.textAlt2 = "GAMEMODE: SINGLEPLAYER";
	gameModeButton.textShown = gameModeButton.textAlt2;
	gameModeButton.shape.width = MeasureText(gameModeButton.textAlt1.data(), defaultFontSize/2) + 30;
	gameModeButton.shape.x = GetScreenWidth() / 2 - gameModeButton.shape.width / 2;
	gameModeButton.shape.y += buttonsPadding;
	//SINGLEPLAYER COLOR = ORANGE
	gameModeButton.defaultColor = ORANGE;
	//MULTIPLAYER COLOR = GOLD
	gameModeButton.secondDefaultColor = GOLD;
	gameModeButton.highlightColor = MAROON;
	gameModeButton.currentColor = gameModeButton.defaultColor;
#pragma endregion

#pragma region TITLE_TEXTS
	titlePart1.content = "pong";
	titlePart1.fontSize = defaultFontSize / 2;
	titlePart1.location.x = GetScreenWidth() / 2 - 130;
	titlePart1.location.y = 100 + titlePart1.fontSize;
	titlePart1.color = WHITE;

	titlePart2.content = "X";
	titlePart2.fontSize = defaultFontSize * 2;
	titlePart2.location.x = GetScreenWidth() / 2 - 70;
	titlePart2.location.y = 100;
	titlePart2.color = RED;

	titlePart3.content = "TREME";
	titlePart3.fontSize = defaultFontSize;
	titlePart3.location.x = GetScreenWidth() / 2 - 15;
	titlePart3.location.y = 100 + titlePart3.fontSize / 2;
	titlePart3.color = YELLOW;
#pragma endregion
}

void MenuScene::Update()
{
	SceneManager::GameMode nextMode = SceneManager::GetCurrentGameMode();

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

	
	if (SceneManager::GetCurrentGameMode() == SceneManager::singlePlayer)
	{
		gameModeButton.currentColor = gameModeButton.defaultColor;
		gameModeButton.textShown = gameModeButton.textAlt2;
	}
	else if (SceneManager::GetCurrentGameMode() == SceneManager::localMultiplayer)
	{
		gameModeButton.currentColor = gameModeButton.secondDefaultColor;
		gameModeButton.textShown = gameModeButton.textAlt1;
	}

	if (IsMouseOnButton(gameModeButton))
	{
		gameModeButton.currentColor = gameModeButton.highlightColor;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			if (SceneManager::GetCurrentGameMode() == SceneManager::singlePlayer)
				nextMode = SceneManager::localMultiplayer;
			else if (SceneManager::GetCurrentGameMode() == SceneManager::localMultiplayer)
				nextMode = SceneManager::singlePlayer;

			SetCurrentGameMode(nextMode);
		}
	}

}

void MenuScene::Draw()
{
	PrintText(titlePart1);
	PrintText(titlePart2);
	PrintText(titlePart3);

	DrawButtonRect(playButton);
	DrawButtonRect(exitButton);
	DrawButtonRect(gameModeButton);

	DrawButtonText(playButton, WHITE, defaultFontSize/2);
	DrawButtonText(exitButton, WHITE, defaultFontSize/2);
	DrawButtonText(gameModeButton, WHITE, defaultFontSize / 2);
}
