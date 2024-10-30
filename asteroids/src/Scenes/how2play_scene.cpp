#include "scenes/how2play_scene.h"

#include "objects/text.h"
#include "objects/button.h"
#include "utils/screen_info.h"
#include "utils/audio_manager.h"

namespace HowToPlayScene
{
	static Text::Text howToPlayTitle;
	static Text::Text controlsTitle;
	static Text::Text leftClickControl;
	static Text::Text rightClickControl;
	static Text::Text objectiveTitle;
	static Text::Text objectiveText;
	static Text::Text powerUpsText;
	static Button::Button backToMenuButton;

	void Init()
	{
		howToPlayTitle = Text::GetText(screenWidth / 2, static_cast<int>(Text::Padding::medium), Text::Fonts::Title1, static_cast<int>(Text::FontSize::big), "HOW TO PLAY", SKYBLUE);
		Text::CenterTextX(howToPlayTitle);

		controlsTitle = Text::GetText(screenWidth / 2, howToPlayTitle.location.y + Text::GetTextHeight(howToPlayTitle) + static_cast<int>(Text::Padding::medium), Text::Fonts::Title2, static_cast<int>(Text::FontSize::big), "CONTROLS", WHITE);
		Text::CenterTextX(controlsTitle);

		leftClickControl = Text::GetText(screenWidth / 2, controlsTitle.location.y + Text::GetTextHeight(controlsTitle) + static_cast<int>(Text::Padding::small), Text::Fonts::Default, static_cast<int>(Text::FontSize::small), "- Left click to SHOOT!", WHITE);
		Text::CenterTextX(leftClickControl);
		rightClickControl = Text::GetText(screenWidth / 2, leftClickControl.location.y + Text::GetTextHeight(leftClickControl) + static_cast<int>(Text::Padding::tiny), Text::Fonts::Default, static_cast<int>(Text::FontSize::small), "- Right click to BOOST MOVEMENT!", WHITE);
		Text::CenterTextX(rightClickControl);

		objectiveTitle = Text::GetText(screenWidth / 2, rightClickControl.location.y + Text::GetTextHeight(rightClickControl) + static_cast<int>(Text::Padding::medium), Text::Fonts::Title2, static_cast<int>(Text::FontSize::big), "OBJECTIVE", WHITE);
		Text::CenterTextX(objectiveTitle);

		objectiveText = Text::GetText(screenWidth / 2, objectiveTitle.location.y + Text::GetTextHeight(objectiveTitle) + static_cast<int>(Text::Padding::small), Text::Fonts::Default, static_cast<int>(Text::FontSize::small), "- Destroy as many planets as you can!", WHITE);
		Text::CenterTextX(objectiveText);

		powerUpsText = Text::GetText(screenWidth / 2, objectiveText.location.y + Text::GetTextHeight(objectiveText) + static_cast<int>(Text::Padding::small), objectiveText.font, objectiveText.fontSize, "- Power-Up: Bullets with no collision!", WHITE);
		Text::CenterTextX(powerUpsText);

		backToMenuButton = Button::GetButton(static_cast<float>(Text::Padding::tiny), screenHeight, 80, 40, "BACK", BLACK, YELLOW, WHITE, Text::Fonts::Default);
		backToMenuButton.shape.y -= backToMenuButton.shape.height + static_cast<float>(Text::Padding::tiny);
	}

	void Update()
	{
		Audio::Update(Audio::Song::menu);
		Button::CheckSceneChange(backToMenuButton, SceneManager::Menu);
	}

	void Draw()
	{
		Text::DrawText(howToPlayTitle);
		Text::DrawText(controlsTitle);
		Text::DrawText(leftClickControl);
		Text::DrawText(rightClickControl);
		Text::DrawText(objectiveTitle);
		Text::DrawText(objectiveText);
		Text::DrawText(powerUpsText);
		Button::DrawButton(backToMenuButton);
	}
}
