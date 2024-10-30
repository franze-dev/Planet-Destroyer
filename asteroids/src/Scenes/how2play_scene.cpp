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
	static Text::Text specialEnemyText;
	static Text::Text ammoText;
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

		objectiveTitle = Text::GetText(screenWidth / 2, rightClickControl.location.y + Text::GetTextHeight(rightClickControl) + static_cast<int>(Text::Padding::small), Text::Fonts::Title2, static_cast<int>(Text::FontSize::big), "OBJECTIVES", WHITE);
		Text::CenterTextX(objectiveTitle);

		objectiveText = Text::GetText(screenWidth / 2, objectiveTitle.location.y + Text::GetTextHeight(objectiveTitle) + static_cast<int>(Text::Padding::small), Text::Fonts::Default, static_cast<int>(Text::FontSize::small), "- Destroy as many planets as you can!", WHITE);
		Text::CenterTextX(objectiveText);

		powerUpsText = Text::GetText(screenWidth / 2, objectiveText.location.y + Text::GetTextHeight(objectiveText) + static_cast<int>(Text::Padding::small), objectiveText.font, objectiveText.fontSize, "- Power-Up: Remove all planets on screen!", WHITE);
		Text::CenterTextX(powerUpsText);

		specialEnemyText = Text::GetText(screenWidth / 2, powerUpsText.location.y + Text::GetTextHeight(powerUpsText) + static_cast<int>(Text::Padding::small), powerUpsText.font, powerUpsText.fontSize, "- Destroy the PLANET DEFENDERS!", WHITE);
		Text::CenterTextX(specialEnemyText);

		ammoText = Text::GetText(screenWidth / 2, specialEnemyText.location.y + Text::GetTextHeight(specialEnemyText) + static_cast<int>(Text::Padding::small), specialEnemyText.font, specialEnemyText.fontSize, "- Click LEFT CLICK once to RELOAD AMMO!", WHITE);
		Text::CenterTextX(ammoText);

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
		Text::DrawText(specialEnemyText);
		Text::DrawText(ammoText);
		Button::DrawButton(backToMenuButton);
	}
}
