#include "result_scene.h"

#include <iostream>
#include <string>

#include "objects/button.h"
#include "objects/text.h"
#include "utils/scene_manager.h"
#include "utils/screen_info.h"

using namespace std;

namespace ResultScene
{
	static int savedScore;
	static Button::Button exitButton;
	static Button::Button backToMenuButton;
	static Button::Button playAgainButton;
	static Text::Text resultText;
	static Text::Text scoreText;

	void SaveScore(int score)
	{
		savedScore = score;
	}

	void Init()
	{
		resultText = Text::GetText(screenWidth / 2, screenHeight / 2 - static_cast<int>(Text::Padding::big), Text::Fonts::Title2, static_cast<int>(Text::FontSize::big), "YOU LOST", RED, YELLOW);
		Text::CenterTextX(resultText);

		scoreText = Text::GetText(screenWidth / 2, resultText.location.y + Text::GetTextHeight(resultText) + static_cast<int>(Text::Padding::tiny), Text::Fonts::Default, resultText.fontSize / 2, "SCORE: ", YELLOW);

		playAgainButton = Button::GetButton(resultText.location.x, resultText.location.y + Text::GetTextHeight(resultText) + static_cast<int>(Text::Padding::medium), Text::GetTextWidth(resultText), Text::GetTextHeight(resultText)/2, "REPLAY", BLACK, MAGENTA, WHITE, Text::Fonts::Default);
		backToMenuButton = Button::GetButton(resultText.location.x, playAgainButton.shape.y + playAgainButton.shape.height + static_cast<int>(Text::Padding::tiny), Text::GetTextWidth(resultText), Text::GetTextHeight(resultText)/2, "MENU", BLACK, SKYBLUE, WHITE, Text::Fonts::Default);
		exitButton = Button::GetButton(backToMenuButton.shape.x, backToMenuButton.shape.y + backToMenuButton.shape.height + static_cast<int>(Text::Padding::tiny), Text::GetTextWidth(resultText), Text::GetTextHeight(resultText)/2, "EXIT", BLACK, RED, WHITE, Text::Fonts::Default);
	}

	void Update()
	{
		Button::CheckSceneChange(exitButton, SceneManager::None);
		Button::CheckSceneChange(backToMenuButton, SceneManager::Menu);
		Button::CheckSceneChange(playAgainButton, SceneManager::Gameplay);

		if (scoreText.content != "SCORE: " + to_string(savedScore))
		{
			scoreText.content += to_string(savedScore);
			Text::CenterTextX(scoreText);
		}
		
	}

	void Draw()
	{
		Button::DrawButton(playAgainButton);
		
		Button::DrawButton(backToMenuButton);
		
		Button::DrawButton(exitButton);

		Text::DrawText(resultText);

		Text::DrawText(scoreText);
	}
}