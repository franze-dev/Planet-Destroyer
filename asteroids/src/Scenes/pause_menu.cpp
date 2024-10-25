#include "pause_menu.h"

#include "raylib.h"

#include "objects/button.h"
#include "utils/scene_manager.h"
#include "utils/screen_info.h"
#include "scenes/gameplay_scene.h"
//NOTE: All of the above are used

namespace PauseMenu
{
	Text::Text pauseTitle;
	Button::Button continueButton;
	Button::Button backToMenuButton;
	Button::Button exitButton;

	int defaultFontSize = 40;
	int buttonsPadding = 30;

	void Init()
	{
		pauseTitle = Text::GetText(screenWidth / 2, screenHeight / 2 - static_cast<int>(Text::FontSize::big), Text::Fonts::Title1, static_cast<int>(Text::FontSize::big), "PAUSED", WHITE);
		Text::CenterTextX(pauseTitle);

		continueButton = Button::GetButton(pauseTitle.location.x, pauseTitle.location.y + Text::GetTextHeight(pauseTitle) + static_cast<float>(Text::Padding::medium), Text::GetTextWidth(pauseTitle), Text::GetTextHeight(pauseTitle) / 2, "CONTINUE", BLACK, MAGENTA, WHITE, Text::Fonts::Default);

		backToMenuButton = Button::GetButton(continueButton.shape.x, continueButton.shape.y + static_cast<float>(Text::Padding::medium), Text::GetTextWidth(pauseTitle), Text::GetTextHeight(pauseTitle) / 2, "BACK TO MENU", BLACK, SKYBLUE, WHITE, Text::Fonts::Default);

		exitButton = Button::GetButton(backToMenuButton.shape.x, backToMenuButton.shape.y + static_cast<float>(Text::Padding::medium), Text::GetTextWidth(pauseTitle), Text::GetTextHeight(pauseTitle) / 2, "EXIT", BLACK, RED, WHITE, Text::Fonts::Default);
	}



	void Update()
	{
		if (Button::IsMouseOnButton(continueButton))
		{
			continueButton.currentColor = continueButton.highlightColor;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				Gameplay::UnPauseGame();;
		}
		else
			continueButton.currentColor = continueButton.defaultColor;

		Button::CheckSceneChange(backToMenuButton, SceneManager::Menu);
		Button::CheckSceneChange(exitButton, SceneManager::None);
	}

	void Draw()
	{
		Text::DrawText(pauseTitle);
		Button::DrawButton(continueButton);
		Button::DrawButton(backToMenuButton);
		Button::DrawButton(exitButton);
	}
}

