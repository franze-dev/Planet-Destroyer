#include "menu_scene.h"

#include "raylib.h"

#include "utils/scene_manager.h"
#include "utils/screen_info.h"
#include "objects/button.h"
//NOTE: All of the above are used

using namespace std;

enum Options
{
	Play,
	Exit
};

static Button::Button playButton;
static Button::Button exitButton;
static Button::Button creditsButton;
static Button::Button howToPlayButton;

static Text::Text titlePart1;
static Text::Text titlePart2;

void MenuScene::Init()
{
#pragma region TITLE_TEXTS

	titlePart1 = Text::GetText(0, 0, Text::Fonts::Title1, static_cast<int>(Text::FontSize::big), "PLANET", MAGENTA);
	titlePart1.location.x = static_cast<float>(screenWidth) / 2.0f - Text::GetTextWidth(titlePart1) / 2.0f;
	titlePart1.location.y = static_cast<float>(Text::Padding::medium);
	titlePart2 = Text::GetText(0, titlePart1.location.y + Text::GetTextHeight(titlePart1) + static_cast<float>(Text::Padding::tiny), Text::Fonts::Title2, static_cast<int>(Text::FontSize::giant), "DESTROYER", YELLOW);
	titlePart2.location.x = static_cast<float>(screenWidth) / 2.0f - Text::GetTextWidth(titlePart2) / 2.0f;
#pragma endregion

	playButton = Button::GetButton(static_cast<float>(GetScreenWidth()) / 2.0f - Text::GetTextWidth(titlePart2) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f - Text::GetTextHeight(titlePart2) / 2.0f, Text::GetTextWidth(titlePart2), Text::GetTextHeight(titlePart2)/2, "PLAY", BLACK, MAGENTA, WHITE, Text::Fonts::Title2);
	
	creditsButton = Button::GetButton(playButton.shape.x, playButton.shape.y + playButton.shape.height + static_cast<int>(Text::Padding::tiny), playButton.shape.width, playButton.shape.height, "CREDITS", BLACK, SKYBLUE, WHITE, playButton.textShown.font);

	exitButton = Button::GetButton(playButton.shape.x, creditsButton.shape.y + creditsButton.shape.height + static_cast<int>(Text::Padding::tiny), playButton.shape.width, playButton.shape.height, "EXIT", BLACK, RED, WHITE, playButton.textShown.font);

	howToPlayButton = Button::GetButton(playButton.shape.x, exitButton.shape.y + exitButton.shape.height + static_cast<int>(Text::Padding::tiny), playButton.shape.width, playButton.shape.height, "HOW TO PLAY", BLACK, YELLOW, WHITE, playButton.textShown.font);
}

void MenuScene::Update()
{
	if (!Audio::IsPlaying(Audio::Song::menu))
		Audio::Play(Audio::Song::menu);

	if (Audio::IsPlaying(Audio::Song::menu))
		Audio::Update(Audio::Song::menu);

	Button::CheckSceneChange(playButton, SceneManager::Gameplay, Audio::Song::menu);

	Button::CheckSceneChange(creditsButton, SceneManager::Credits);

	Button::CheckSceneChange(exitButton, SceneManager::None, Audio::Song::menu);

}

void MenuScene::Draw()
{
	DrawText(titlePart1);
	DrawText(titlePart2);

	Button::DrawButton(playButton);
	Button::DrawButton(exitButton);
	Button::DrawButton(creditsButton);

}
