#include "credits_scene.h"

#include "button.h"
#include "screen_info.h"
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
		soundTool
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

	static const int maxCredits = soundTool + 1;

	static Page page1{};
	static Page page2{};
	static Page page3{};

	static Text::Text creditsTitle;
	static Text::Text devTitle;
	static Text::Text artTitle;
	static Text::Text fontTitle;
	static Text::Text toolsTitle;

	static Button::Button backToMenuButton;

	static Credit creditsInfo[maxCredits];
	static Pages currentPage = Pages::page1;

	static void CheckURLButton(Credit& credit)
	{
		if (Button::IsMouseOnButton(credit.button))
		{
			credit.button.currentColor = credit.button.highlightColor;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				OpenURL(credit.url.data());
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

			for (int i = language; i < soundTool + 1; i++)
				CheckURLButton(creditsInfo[i]);

			break;
		default:
			break;
		}

	}

	static void CheckPagesButton(Page& page)
	{
		if (Button::IsMouseOnButton(page.button))
		{
			page.button.currentColor = page.button.highlightColor;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				if (currentPage != page.number)
					currentPage = page.number;
		}
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
		credit.button = Button::GetButton(screenWidth / 2, credit.text.location.y + Text::GetTextHeight(credit.text) + static_cast<int>(Text::Padding::small), Text::GetTextWidth(creditsTitle) + static_cast<int>(Text::Padding::medium), Text::GetTextHeight(credit.text) * 2, credit.name, BLACK, highlightColor, WHITE, Text::Fonts::Default);
		credit.button.shape.x -= credit.button.shape.width / 2;
	}

	static void InitCredits()
	{
#pragma region PAGE_1

		creditsTitle = Text::GetText(screenWidth / 2, static_cast<int>(Text::Padding::medium), Text::Fonts::Title1, static_cast<int>(Text::FontSize::big), "CREDITS", SKYBLUE);
		Text::CenterTextX(creditsTitle);

		devTitle = Text::GetText(screenWidth / 2, creditsTitle.location.y + Text::GetTextHeight(creditsTitle) + static_cast<int>(Text::Padding::small), Text::Fonts::Title2, creditsTitle.fontSize * 3 / 4, "DEVELOPMENT", MAGENTA);
		Text::CenterTextX(devTitle);

		InitCredit(creditsInfo[dev], devTitle.location.y + Text::GetTextHeight(devTitle) + static_cast<int>(Text::Padding::small));

		artTitle = Text::GetText(screenWidth / 2, creditsInfo[dev].button.shape.y + creditsInfo[dev].button.shape.height + static_cast<int>(Text::Padding::medium), Text::Fonts::Title2, devTitle.fontSize, "ART", YELLOW);
		Text::CenterTextX(artTitle);

		InitCredit(creditsInfo[artist], artTitle.location.y + Text::GetTextHeight(artTitle) + static_cast<int>(Text::Padding::small));

#pragma endregion

#pragma region PAGE_2

		fontTitle = Text::GetText(screenWidth / 2, devTitle.location.y, artTitle.font, artTitle.fontSize, "FONTS", artTitle.currentColor);
		Text::CenterTextX(fontTitle);

		float posY = fontTitle.location.y + Text::GetTextHeight(fontTitle) + static_cast<float>(Text::Padding::small);

		for (int i = font1; i < font3 + 1; i++)
		{
			InitCredit(creditsInfo[i], posY);

			posY += creditsInfo[i].button.shape.height + static_cast<int>(Text::Padding::big);
		}

#pragma endregion

#pragma region PAGE_3

		toolsTitle = fontTitle;
		toolsTitle.content = "TOOLS";

		posY = toolsTitle.location.y + Text::GetTextHeight(toolsTitle) + static_cast<float>(Text::Padding::small);

		for (int i = language; i < soundTool + 1; i++)
		{
			InitCredit(creditsInfo[i], posY);

			posY += creditsInfo[i].button.shape.height + static_cast<int>(Text::Padding::medium);
		}

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

		creditsInfo[language].name = "C++";
		creditsInfo[language].url = "https://isocpp.org/";
		creditsInfo[language].role = "CODE";

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

		creditsInfo[soundTool].name = "Sound!";
		creditsInfo[soundTool].url = "https://www.piskelapp.com/";
		creditsInfo[soundTool].role = "SOUND TOOL";

#pragma endregion


#pragma endregion

		InitCredits();

#pragma region PAGES

		page2.button = Button::GetButton(screenWidth / 2, screenHeight, 40.0f, 40.0f, "2", WHITE, SKYBLUE, BLACK, Text::Fonts::Default);
		page2.button.shape.x -= page2.button.shape.width / 2;
		page2.button.shape.y -= page2.button.shape.height + static_cast<float>(Text::Padding::small);
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

		backToMenuButton = Button::GetButton(static_cast<float>(Text::Padding::small), screenHeight, 80, 40, "BACK", BLACK, YELLOW, WHITE, Text::Fonts::Default);
		backToMenuButton.shape.y -= backToMenuButton.shape.height + static_cast<float>(Text::Padding::small);

	}

	void Update()
	{
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

			for (int i = language; i < soundTool + 1; i++)
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