#include "credits.h"

#include "ui_manager.h"
#include "constants.h"

namespace Credits
{
	struct Credit
	{
		string name;
		string url;
		string role;
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

	static void InitCredit(Credit& credit, float x, float y)
	{
		
	}

	static void InitCredits()
	{
		creditsTitle = UIManager::GetText(screenWidth / 2, static_cast<int>(UIManager::Padding::medium), UIManager::Fonts::Title1, static_cast<int>(UIManager::FontSize::big), "CREDITS", SKYBLUE);

		devTitle = UIManager::GetText(creditsTitle.location.x, creditsTitle.location.y + UIManager::GetTextHeight(creditsTitle) + static_cast<int>(UIManager::Padding::small), creditsTitle.font, creditsTitle.fontSize * 3 / 4, "DEV", MAGENTA);
		
		InitCredit(creditsInfo[dev], devTitle.location.x, devTitle.location.y + UIManager::GetTextHeight(devTitle) + static_cast<int>(UIManager::Padding::small));

		artTitle = devTitle;
		fontTitle = creditsTitle;
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
	}

	void Draw()
	{

	}
}