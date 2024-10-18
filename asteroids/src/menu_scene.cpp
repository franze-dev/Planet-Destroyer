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
static UIManager::Button creditsButton;

static UIManager::Text titlePart1;
static UIManager::Text titlePart2;

void MenuScene::Init()
{
#pragma region TITLE_TEXTS

	titlePart1 = UIManager::GetText(0, 0, UIManager::Fonts::Title1, static_cast<int>(UIManager::FontSize::big), "PLANET", MAGENTA);
	titlePart1.location.x = static_cast<float>(screenWidth) / 2.0f - UIManager::GetTextWidth(titlePart1) / 2.0f;
	titlePart1.location.y = static_cast<float>(UIManager::Padding::medium);
	titlePart2 = UIManager::GetText(0, titlePart1.location.y + UIManager::GetTextHeight(titlePart1) + static_cast<float>(UIManager::Padding::small), UIManager::Fonts::Title2, static_cast<int>(UIManager::FontSize::big2), "DESTROYER", YELLOW);
	titlePart2.location.x = static_cast<float>(screenWidth) / 2.0f - UIManager::GetTextWidth(titlePart2) / 2.0f;
#pragma endregion

	playButton = UIManager::GetButton(static_cast<float>(GetScreenWidth()) / 2.0f - UIManager::GetTextWidth(titlePart2) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f - UIManager::GetTextHeight(titlePart2) / 2.0f, UIManager::GetTextWidth(titlePart2), UIManager::GetTextHeight(titlePart2)/2, "PLAY", BLACK, MAGENTA, YELLOW, UIManager::Fonts::Title2);
	
	creditsButton = UIManager::GetButton(playButton.shape.x, playButton.shape.y + playButton.shape.height + static_cast<int>(UIManager::Padding::small), playButton.shape.width, playButton.shape.height, "CREDITS", BLACK, SKYBLUE, YELLOW, playButton.textShown.font);

	exitButton = UIManager::GetButton(playButton.shape.x, creditsButton.shape.y + creditsButton.shape.height + static_cast<int>(UIManager::Padding::small), playButton.shape.width, playButton.shape.height, "EXIT", BLACK, RED, YELLOW, playButton.textShown.font);

}

void MenuScene::Update()
{
	UIManager::CheckSceneChange(playButton, SceneManager::Gameplay);

	UIManager::CheckSceneChange(creditsButton, SceneManager::Credits);

	UIManager::CheckSceneChange(exitButton, SceneManager::None);

}

void MenuScene::Draw()
{
	PrintText(titlePart1);
	PrintText(titlePart2);

	UIManager::DrawButton(playButton);
	UIManager::DrawButton(exitButton);
	UIManager::DrawButton(creditsButton);

}
