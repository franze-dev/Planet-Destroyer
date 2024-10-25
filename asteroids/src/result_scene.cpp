#include "result_scene.h"

#include <iostream>

#include "button.h"
#include "text.h"
#include "scene_manager.h"
#include "screen_info.h"
using namespace std;

namespace ResultScene
{
	static SpaceShip::SpaceShip savedShip;
	static Button::Button exitButton;
	static Button::Button backToMenuButton;
	static Button::Button playAgainButton;
	static Text::Text resultText;
	static string win = "WON!";
	static string lose = "LOST!";

	void SaveShip(SpaceShip::SpaceShip ship)
	{
		savedShip = ship;
	}

	void Init()
	{
		resultText = Text::GetText(screenWidth / 2, screenHeight / 2 - static_cast<int>(Text::Padding::big), Text::Fonts::Title2, static_cast<int>(Text::FontSize::big), "YOU ", RED, YELLOW);
		Text::CenterTextX(resultText);

		playAgainButton = Button::GetButton(resultText.location.x, resultText.location.y + Text::GetTextHeight(resultText) + static_cast<int>(Text::Padding::medium), Text::GetTextWidth(resultText), Text::GetTextHeight(resultText)/2, "REPLAY", BLACK, MAGENTA, WHITE, Text::Fonts::Default);
		backToMenuButton = Button::GetButton(resultText.location.x, playAgainButton.shape.y + playAgainButton.shape.height + static_cast<int>(Text::Padding::small), Text::GetTextWidth(resultText), Text::GetTextHeight(resultText)/2, "MENU", BLACK, SKYBLUE, WHITE, Text::Fonts::Default);
		exitButton = Button::GetButton(backToMenuButton.shape.x, backToMenuButton.shape.y + backToMenuButton.shape.height + static_cast<int>(Text::Padding::small), Text::GetTextWidth(resultText), Text::GetTextHeight(resultText)/2, "EXIT", BLACK, RED, WHITE, Text::Fonts::Default);
	}

	void Update()
	{
		Button::CheckSceneChange(exitButton, SceneManager::None);
		Button::CheckSceneChange(backToMenuButton, SceneManager::Menu);
		Button::CheckSceneChange(playAgainButton, SceneManager::Gameplay);


		if (savedShip.won)
		{
			resultText.currentColor = resultText.alt2Color;
			resultText.content += win;
			resultText.location.x = screenWidth / 2;
			Text::CenterTextX(resultText);
		}
		else if (resultText.content != "YOU LOST!")
		{
			resultText.currentColor = resultText.alt1Color;
			resultText.content += lose;
			resultText.location.x = screenWidth / 2;
			Text::CenterTextX(resultText);
		}
	}

	void Draw()
	{
		Button::DrawButton(playAgainButton);
		
		Button::DrawButton(backToMenuButton);
		
		Button::DrawButton(exitButton);

		Text::DrawText(resultText);
	}
}