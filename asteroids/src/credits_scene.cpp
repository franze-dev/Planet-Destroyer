#include "credits_scene.h"

#include "ui_manager.h"
#include "screen_info.h"

namespace CreditsScene
{
	struct Credit
	{
		string name;
		string url;
		string role;
		UIManager::Text text;
		UIManager::Button button;
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
		UIManager::Button button;
		Pages number;
	};

	static const int maxCredits = soundTool + 1;

	static Page page1{};
	static Page page2{};
	static Page page3{};

	static UIManager::Text creditsTitle;
	static UIManager::Text devTitle;
	static UIManager::Text artTitle;
	static UIManager::Text fontTitle;
	static UIManager::Text toolsTitle;

	static Credit creditsInfo[maxCredits];
	static Pages currentPage = Pages::page1;

	static void CheckURLButton(Credit& credit)
	{
		if (UIManager::IsMouseOnButton(credit.button))
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
			break;
		default:
			break;
		}

	}

	static void CheckPagesButton(Page& page)
	{
		if (UIManager::IsMouseOnButton(page.button))
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

		credit.text = UIManager::GetText(screenWidth / 2, y, UIManager::Fonts::Default, static_cast<int>(UIManager::FontSize::medium), credit.role, WHITE);
		UIManager::CenterTextX(credit.text);
		credit.button = UIManager::GetButton(screenWidth / 2, credit.text.location.y + UIManager::GetTextHeight(credit.text) + static_cast<int>(UIManager::Padding::small), UIManager::GetTextWidth(creditsTitle) + static_cast<int>(UIManager::Padding::medium), UIManager::GetTextHeight(credit.text), credit.name, BLACK, highlightColor, WHITE, UIManager::Fonts::Default);
		credit.button.shape.x -= credit.button.shape.width / 2;
	}

	static void InitCredits()
	{
#pragma region PAGE_1

		creditsTitle = UIManager::GetText(screenWidth / 2, static_cast<int>(UIManager::Padding::medium), UIManager::Fonts::Title1, static_cast<int>(UIManager::FontSize::big), "CREDITS", SKYBLUE);
		UIManager::CenterTextX(creditsTitle);

		devTitle = UIManager::GetText(screenWidth / 2, creditsTitle.location.y + UIManager::GetTextHeight(creditsTitle) + static_cast<int>(UIManager::Padding::small), UIManager::Fonts::Title2, creditsTitle.fontSize * 3 / 4, "DEVELOPMENT", MAGENTA);
		UIManager::CenterTextX(devTitle);

		InitCredit(creditsInfo[dev], devTitle.location.y + UIManager::GetTextHeight(devTitle) + static_cast<int>(UIManager::Padding::small));

		artTitle = UIManager::GetText(screenWidth / 2, creditsInfo[dev].button.shape.y + creditsInfo[dev].button.shape.height + static_cast<int>(UIManager::Padding::medium), UIManager::Fonts::Title2, devTitle.fontSize, "ART", YELLOW);
		UIManager::CenterTextX(artTitle);

		InitCredit(creditsInfo[artist], artTitle.location.y + UIManager::GetTextHeight(artTitle) + static_cast<int>(UIManager::Padding::small));

#pragma endregion

#pragma region PAGE_2

		fontTitle = UIManager::GetText(screenWidth / 2, devTitle.location.y, artTitle.font, artTitle.fontSize, "FONTS", artTitle.currentColor);
		UIManager::CenterTextX(fontTitle);

		float posY = fontTitle.location.y + UIManager::GetTextHeight(fontTitle) + static_cast<float>(UIManager::Padding::small);

		for (int i = font1; i < font3 + 1; i++)
		{
			InitCredit(creditsInfo[i], posY);

			posY += creditsInfo[i].button.shape.height + static_cast<int>(UIManager::Padding::big);
		}

#pragma endregion

#pragma region PAGE_3

		toolsTitle = fontTitle;
		toolsTitle.content = "TOOLS";

		posY = toolsTitle.location.y + UIManager::GetTextHeight(toolsTitle) + static_cast<float>(UIManager::Padding::small);

		for (int i = language; i < soundTool + 1; i++)
		{
			InitCredit(creditsInfo[i], posY);

			posY += creditsInfo[i].button.shape.height + static_cast<int>(UIManager::Padding::big);
		}

#pragma endregion

	}

	static void DrawCredit(Credit& credit)
	{
		UIManager::PrintText(credit.text);

		UIManager::DrawButton(credit.button);
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
		creditsInfo[font3].url = "https://gensofi24.itch.io/";
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

		creditsInfo[artTool].name = "ART TOOL";
		creditsInfo[artTool].url = "https://www.piskelapp.com/";
		creditsInfo[artTool].role = "PISKEL";

#pragma endregion

#pragma region SOUND_TOOL

		creditsInfo[artTool].name = "SOUND TOOL";
		creditsInfo[artTool].url = "https://www.piskelapp.com/";
		creditsInfo[artTool].role = "Sound!";

#pragma endregion


#pragma endregion

		InitCredits();

#pragma region PAGES

		page2.button = UIManager::GetButton(screenWidth / 2, screenHeight, 40.0f, 40.0f, "2", WHITE, SKYBLUE, BLACK, UIManager::Fonts::Default);
		page2.button.shape.x -= page2.button.shape.width / 2;
		page2.button.shape.y -= page2.button.shape.height + static_cast<float>(UIManager::Padding::small);
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

	}

	void Update()
	{
		CheckURLButtons();

		CheckPagesButton(page1);
		CheckPagesButton(page2);
		CheckPagesButton(page3);
	}

	void Draw()
	{
		UIManager::PrintText(creditsTitle);

		switch (currentPage)
		{
		case CreditsScene::Pages::page1:

			UIManager::PrintText(devTitle);
			DrawCredit(creditsInfo[dev]);

			UIManager::PrintText(artTitle);
			DrawCredit(creditsInfo[artist]);

			break;
		case CreditsScene::Pages::page2:

			UIManager::PrintText(fontTitle);

			for (int i = font1; i < font3 + 1; i++)
				DrawCredit(creditsInfo[i]);

			break;
		case CreditsScene::Pages::page3:

			UIManager::PrintText(toolsTitle);

			for (int i = language; i < soundTool; i++)
				DrawCredit(creditsInfo[i]);

			break;
		default:
			break;
		}

		UIManager::DrawButton(page1.button);
		UIManager::DrawButton(page2.button);
		UIManager::DrawButton(page3.button);

	}
}