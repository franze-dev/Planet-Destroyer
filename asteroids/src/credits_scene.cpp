#include "credits_scene.h"

#include "ui_manager.h"
#include "constants.h"

namespace Credits
{
	struct Credit
	{
		string name;
		string url;
		string role;
		UIManager::Text text;
		UIManager::Button button;
	};

	enum People
	{
		dev,
		artist,
		font1,
		font2,
		font3
	};

	enum Pages
	{
		page1,
		page2
	};

	static const int maxCredits = 5;

	static UIManager::Text creditsTitle;
	static UIManager::Text devTitle;
	static UIManager::Text artTitle;
	static UIManager::Text fontTitle;
	static Credit creditsInfo[maxCredits];

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
		for (int i = 0; i < maxCredits; i++)
			CheckURLButton(creditsInfo[i]);
	}

	static void InitCredit(Credit& credit, float x, float y)
	{
		Color highlightColor = YELLOW;

		if (credit.name == creditsInfo[dev].name)
			highlightColor = MAGENTA;

		credit.text = UIManager::GetText(x, y, UIManager::Fonts::Default, static_cast<int>(UIManager::FontSize::medium), credit.role, WHITE);
		credit.button = UIManager::GetButton(credit.text.location.x, credit.text.location.y + UIManager::GetTextHeight(credit.text) + static_cast<int>(UIManager::Padding::small), UIManager::GetTextWidth(credit.text), UIManager::GetTextHeight(credit.text), credit.name, BLACK, highlightColor, WHITE, UIManager::Fonts::Default);
	}

	static void InitCredits()
	{
		creditsTitle = UIManager::GetText(screenWidth / 2, static_cast<int>(UIManager::Padding::medium), UIManager::Fonts::Title1, static_cast<int>(UIManager::FontSize::big), "CREDITS", SKYBLUE);

		devTitle = UIManager::GetText(creditsTitle.location.x, creditsTitle.location.y + UIManager::GetTextHeight(creditsTitle) + static_cast<int>(UIManager::Padding::small), UIManager::Fonts::Title2, creditsTitle.fontSize * 3 / 4, "DEV", MAGENTA);

		InitCredit(creditsInfo[dev], devTitle.location.x, devTitle.location.y + UIManager::GetTextHeight(devTitle) + static_cast<int>(UIManager::Padding::small));

		artTitle = UIManager::GetText(devTitle.location.x, creditsInfo[dev].button.shape.y + creditsInfo[dev].button.shape.height + static_cast<int>(UIManager::Padding::medium), UIManager::Fonts::Title2, devTitle.fontSize, "ARTIST", YELLOW);
		
		InitCredit(creditsInfo[artist], devTitle.location.x, artTitle.location.y + UIManager::GetTextHeight(artTitle) + static_cast<int>(UIManager::Padding::small));
		
		fontTitle = UIManager::GetText(devTitle.location.x, creditsInfo[artist].button.shape.y + creditsInfo[artist].button.shape.height + static_cast<int>(UIManager::Padding::small), artTitle.font, artTitle.fontSize, "FONTS", artTitle.currentColor);

		float posY = fontTitle.location.y + UIManager::GetTextHeight(fontTitle) + static_cast<float>(UIManager::Padding::small);

		for (int i = font1; i < font3 + 1; i++)
		{
			InitCredit(creditsInfo[i], fontTitle.location.x, posY);

			posY += creditsInfo[i].button.shape.height + static_cast<int>(UIManager::Padding::small);
		}
	}

	void DrawCredit(Credit& credit)
	{
		UIManager::PrintText(credit.text);
		UIManager::DrawButton(credit.button);
	}

	void Init()
	{
#pragma region CREDITS_INFO

#pragma region DEV_ROLE
		//DEV (ME)
		creditsInfo[dev].name = "Sofia Alvarez Franze";
		creditsInfo[dev].url = "https://gensofi24.itch.io/";
		creditsInfo[dev].role = "DEV";
#pragma endregion

#pragma region ART_ROLE
		//ART (ME, FOR NOW)
		creditsInfo[artist].name = "Sofia Alvarez Franze";
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


#pragma endregion

		InitCredits();
	}

	void Update()
	{
		CheckURLButtons();
	}

	void Draw()
	{
		UIManager::PrintText(devTitle);
		DrawCredit(creditsInfo[dev]);

		UIManager::PrintText(artTitle);
		DrawCredit(creditsInfo[artist]);

		UIManager::PrintText(fontTitle);

		for (int i = font1; i < font3 + 1; i++)
			DrawCredit(creditsInfo[artist]);

	}
}