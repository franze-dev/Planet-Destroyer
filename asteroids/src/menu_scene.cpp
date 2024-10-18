#include "menu_scene.h"

#include "raylib.h"

#include <iostream>
#include <string>

#include "scene_manager.h"
#include "button.h"
#include "screen_info.h"

using namespace std;

enum Options
{
	Play,
	Exit
};

static Button::Button playButton;
static Button::Button exitButton;
static Button::Button creditsButton;

static Text::Text titlePart1;
static Text::Text titlePart2;

void MenuScene::Init()
{
#pragma region TITLE_TEXTS

	titlePart1 = Text::GetText(0, 0, Text::Fonts::Title1, static_cast<int>(Text::FontSize::big), "PLANET", MAGENTA);
	titlePart1.location.x = static_cast<float>(screenWidth) / 2.0f - Text::GetTextWidth(titlePart1) / 2.0f;
	titlePart1.location.y = static_cast<float>(Text::Padding::medium);
	titlePart2 = Text::GetText(0, titlePart1.location.y + Text::GetTextHeight(titlePart1) + static_cast<float>(Text::Padding::small), Text::Fonts::Title2, static_cast<int>(Text::FontSize::giant), "DESTROYER", YELLOW);
	titlePart2.location.x = static_cast<float>(screenWidth) / 2.0f - Text::GetTextWidth(titlePart2) / 2.0f;
#pragma endregion

	playButton = Button::GetButton(static_cast<float>(GetScreenWidth()) / 2.0f - Text::GetTextWidth(titlePart2) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f - Text::GetTextHeight(titlePart2) / 2.0f, Text::GetTextWidth(titlePart2), Text::GetTextHeight(titlePart2)/2, "PLAY", BLACK, MAGENTA, YELLOW, Text::Fonts::Title2);
	
	creditsButton = Button::GetButton(playButton.shape.x, playButton.shape.y + playButton.shape.height + static_cast<int>(Text::Padding::small), playButton.shape.width, playButton.shape.height, "CREDITS", BLACK, SKYBLUE, YELLOW, playButton.textShown.font);

	exitButton = Button::GetButton(playButton.shape.x, creditsButton.shape.y + creditsButton.shape.height + static_cast<int>(Text::Padding::small), playButton.shape.width, playButton.shape.height, "EXIT", BLACK, RED, YELLOW, playButton.textShown.font);

}

void MenuScene::Update()
{
	Button::CheckSceneChange(playButton, SceneManager::Gameplay);

	Button::CheckSceneChange(creditsButton, SceneManager::Credits);

	Button::CheckSceneChange(exitButton, SceneManager::None);

}

void MenuScene::Draw()
{
	PrintText(titlePart1);
	PrintText(titlePart2);

	Button::DrawButton(playButton);
	Button::DrawButton(exitButton);
	Button::DrawButton(creditsButton);

}
