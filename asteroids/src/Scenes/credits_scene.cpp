#include "credits_scene.h"

#include "objects/button.h"
#include "utils/screen_info.h"
//NOTE: All of the above are used

namespace CreditsScene
{
	struct Credit
	{
		string name;
		string url;
		string role;
		Text::Text text;
		Button::Button button;
	};

	enum Roles
	{
		dev,
		artist,
		font1,
		font2,
		font3,
		language,
		library,
		artTool,
		soundTool1,
		soundTool2
	};

	enum class Pages
	{
		page1,
		page2,
		page3
	};

	struct Page
	{
		Button::Button button;
		Pages number;
	};

	static const int maxCredits = soundTool2 + 1;

	static Page page1{};
	static Page page2{};
	static Page page3{};

	static Text::Text creditsTitle;
	static Text::Text devTitle;
	static Text::Text artTitle;
	static Text::Text fontTitle;
	static Text::Text toolsTitle;

	static Text::Text soundSubTitle;

	static Button::Button backToMenuButton;

	static Credit creditsInfo[maxCredits];
	static Pages currentPage = Pages::page1;

	static void CheckURLButton(Credit& credit)
	{
		Audio::ButtonSfx sfx{};

		sfx = Audio::GetRandomSfx();

		if (Button::IsMouseOnButton(credit.button))
		{
			credit.button.currentColor = credit.button.highlightColor;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				if (!Audio::IsPlaying(sfx))
					Audio::Play(sfx);
				OpenURL(credit.url.c_str());
			}
		}
		else
			credit.button.currentColor = credit.button.defaultColor;
	}

	static void CheckURLButtons()
	{
		switch (currentPage)
		{
		case CreditsScene::Pages::page1:

			for (int i = dev; i < artist + 1; i++)
				CheckURLButton(creditsInfo[i]);

			break;
		case CreditsScene::Pages::page2:

			for (int i = font1; i < font3 + 1; i++)
				CheckURLButton(creditsInfo[i]);

			break;
		case CreditsScene::Pages::page3:

			for (int i = language; i < soundTool2 + 1; i++)
				CheckURLButton(creditsInfo[i]);

			//both sound buttons

			break;
		default:
			break;
		}

	}

	static void CheckPagesButton(Page& page)
	{
		Audio::ButtonSfx sfx{};

		if (Button::IsMouseOnButton(page.button))
		{
			sfx = Audio::GetRandomSfx();

			page.button.currentColor = page.button.highlightColor;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				if (!Audio::IsPlaying(sfx))
					Audio::Play(sfx);
				if (currentPage != page.number)
					currentPage = page.number;
			}
		}
		else if (currentPage == page.number)
			page.button.currentColor = page.button.highlightColor;
		else
			page.button.currentColor = page.button.defaultColor;
	}

	static void InitCredit(Credit& credit, float y)
	{
		Color highlightColor = SKYBLUE;

		if (credit.name == creditsInfo[dev].name)
			highlightColor = MAGENTA;

		credit.text = Text::GetText(screenWidth / 2, y, Text::Fonts::Default, static_cast<int>(Text::FontSize::small), credit.role, WHITE);
		Text::CenterTextX(credit.text);
		credit.button = Button::GetButton(screenWidth / 2, credit.text.location.y + Text::GetTextHeight(credit.text) + static_cast<int>(Text::Padding::tiny), Text::GetTextWidth(creditsTitle) + static_cast<int>(Text::Padding::giant), Text::GetTextHeight(credit.text) * 2, credit.name, BLACK, highlightColor, WHITE, Text::Fonts::Default);
		credit.button.shape.x -= credit.button.shape.width / 2;
	}

	static void InitCredits()
	{
		creditsTitle = Text::GetText(screenWidth / 2, static_cast<int>(Text::Padding::medium), Text::Fonts::Title1, static_cast<int>(Text::FontSize::big), "CREDITS", SKYBLUE);
		Text::CenterTextX(creditsTitle);

#pragma region PAGE_1

		devTitle = Text::GetText(screenWidth / 2, creditsTitle.location.y + Text::GetTextHeight(creditsTitle) + static_cast<int>(Text::Padding::tiny), Text::Fonts::Title2, creditsTitle.fontSize * 3 / 4, "DEVELOPMENT", MAGENTA);
		Text::CenterTextX(devTitle);

		InitCredit(creditsInfo[dev], devTitle.location.y + Text::GetTextHeight(devTitle) + static_cast<int>(Text::Padding::tiny));

		artTitle = Text::GetText(screenWidth / 2, creditsInfo[dev].button.shape.y + creditsInfo[dev].button.shape.height + static_cast<int>(Text::Padding::medium), Text::Fonts::Title2, devTitle.fontSize, "ART", YELLOW);
		Text::CenterTextX(artTitle);

		InitCredit(creditsInfo[artist], artTitle.location.y + Text::GetTextHeight(artTitle) + static_cast<int>(Text::Padding::tiny));

#pragma endregion

#pragma region PAGE_2

		fontTitle = Text::GetText(screenWidth / 2, devTitle.location.y, artTitle.font, artTitle.fontSize, "FONTS", artTitle.currentColor);
		Text::CenterTextX(fontTitle);

		float posY = fontTitle.location.y + Text::GetTextHeight(fontTitle) + static_cast<float>(Text::Padding::tiny);

		for (int i = font1; i < font3 + 1; i++)
		{
			InitCredit(creditsInfo[i], posY);

			posY += creditsInfo[i].button.shape.height + static_cast<int>(Text::Padding::big);
		}

#pragma endregion

#pragma region PAGE_3

		toolsTitle = fontTitle;
		toolsTitle.content = "TOOLS";

		posY = toolsTitle.location.y + Text::GetTextHeight(toolsTitle) + static_cast<float>(Text::Padding::tiny);

		for (int i = language; i < soundTool2 + 1; i++)
		{
			InitCredit(creditsInfo[i], posY);

			posY += creditsInfo[i].button.shape.height + Text::GetTextHeight(creditsInfo[i].text) + static_cast<int>(Text::Padding::small);
		}

		//both sound buttons

#pragma endregion

	}

	static void DrawCredit(Credit& credit)
	{
		Text::DrawText(credit.text);

		Button::DrawButton(credit.button);
	}

	void Init()
	{
#pragma region CREDITS_INFO

#pragma region DEV_ROLE
		//DEV (ME)
		creditsInfo[dev].name = "Sofia Alvarez";
		creditsInfo[dev].url = "https://gensofi24.itch.io/";
		creditsInfo[dev].role = "DEV";
#pragma endregion

#pragma region ART_ROLE
		//ART (ME, FOR NOW)
		creditsInfo[artist].name = "Sofia Alvarez";
		creditsInfo[artist].url = "https://gensofi24.itch.io/";
		creditsInfo[artist].role = "PIXEL ART";
#pragma endregion

#pragma region FONTS_ROLE
		//FONTS
		//title1
		creditsInfo[font1].name = "AIR AMERICA by Saja Typeworks";
		creditsInfo[font1].url = "https://www.fontsquirrel.com/fonts/air-america";
		creditsInfo[font1].role = "TITLE FONT 1";

		//title2
		creditsInfo[font2].name = "BLACKOUT by The League of Moveable Type";
		creditsInfo[font2].url = "https://www.fontsquirrel.com/fonts/blackout";
		creditsInfo[font2].role = "TITLE FONT 2";

		//default text
		creditsInfo[font3].name = "COURIER PRIME by Quote-Unquote Apps";
		creditsInfo[font3].url = "https://www.fontsquirrel.com/fonts/courier-prime";
		creditsInfo[font3].role = "DEFAULT FONT";
#pragma endregion

#pragma region LANGUAGE_TOOL

		creditsInfo[language].name = "Github Repository";
		creditsInfo[language].url = "https://github.com/aeffggbh/Asteroids";
		creditsInfo[language].role = "SOURCE CODE";

#pragma endregion

#pragma region LIBRARY_TOOL

		creditsInfo[library].name = "RAYLIB";
		creditsInfo[library].url = "https://www.raylib.com/index.html";
		creditsInfo[library].role = "LIBRARY";

#pragma endregion

#pragma region ART_TOOL

		creditsInfo[artTool].name = "PISKEL";
		creditsInfo[artTool].url = "https://www.piskelapp.com/";
		creditsInfo[artTool].role = "ART TOOL";

#pragma endregion

#pragma region SOUND_TOOL

		creditsInfo[soundTool1].name = "Made with Suno AI";
		creditsInfo[soundTool1].url = "https://suno.com/";
		creditsInfo[soundTool1].role = "MUSIC";

		creditsInfo[soundTool2].name = "Sci-fi sounds by Kenney";
		creditsInfo[soundTool2].url = "https://kenney.nl/assets/sci-fi-sounds";
		creditsInfo[soundTool2].role = "SFX";

#pragma endregion


#pragma endregion

		InitCredits();

#pragma region PAGES

		page2.button = Button::GetButton(screenWidth / 2, screenHeight, 40.0f, 40.0f, "2", WHITE, SKYBLUE, BLACK, Text::Fonts::Default);
		page2.button.shape.x -= page2.button.shape.width / 2;
		page2.button.shape.y -= page2.button.shape.height + static_cast<float>(Text::Padding::tiny);
		page2.number = Pages::page2;

		page1.button = page2.button;
		page1.button.textShown.content = "1";
		page1.button.shape.x -= page1.button.shape.width * 2;
		page1.number = Pages::page1;

		page3.button = page1.button;
		page3.button.textShown.content = "3";
		page3.button.shape.x += page3.button.shape.width * 3 + page2.button.shape.width;
		page3.number = Pages::page3;

#pragma endregion

		backToMenuButton = Button::GetButton(static_cast<float>(Text::Padding::tiny), screenHeight, 80, 40, "BACK", BLACK, YELLOW, WHITE, Text::Fonts::Default);
		backToMenuButton.shape.y -= backToMenuButton.shape.height + static_cast<float>(Text::Padding::tiny);

	}

	void Update()
	{
		Audio::Update(Audio::Song::menu);
		CheckURLButtons();
		Button::CheckSceneChange(backToMenuButton, SceneManager::Menu);

		CheckPagesButton(page1);
		CheckPagesButton(page2);
		CheckPagesButton(page3);
	}

	void Draw()
	{
		Text::DrawText(creditsTitle);

		switch (currentPage)
		{
		case CreditsScene::Pages::page1:

			Text::DrawText(devTitle);
			DrawCredit(creditsInfo[dev]);

			Text::DrawText(artTitle);
			DrawCredit(creditsInfo[artist]);

			break;
		case CreditsScene::Pages::page2:

			Text::DrawText(fontTitle);

			for (int i = font1; i < font3 + 1; i++)
				DrawCredit(creditsInfo[i]);

			break;
		case CreditsScene::Pages::page3:

			Text::DrawText(toolsTitle);

			for (int i = language; i < soundTool2 + 1; i++)
				DrawCredit(creditsInfo[i]);

			break;
		default:
			break;
		}

		Button::DrawButton(page1.button);
		Button::DrawButton(page2.button);
		Button::DrawButton(page3.button);
		Button::DrawButton(backToMenuButton);
	}
}