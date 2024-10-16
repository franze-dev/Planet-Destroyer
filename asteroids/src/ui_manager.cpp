#include "UI_Manager.h"

namespace UIManager
{
	static Font titleFont1;
	static Font titleFont2;
	static Font generalText;

	float GetTextWidth(Text text)
	{
		return MeasureTextEx(GetFont(text.font), text.content.data(), static_cast<float>(text.fontSize), textSpacing).x;
	}

	float GetTextHeight(Text text)
	{
		return MeasureTextEx(GetFont(text.font), text.content.data(), static_cast<float>(text.fontSize), textSpacing).y;
	}

	Font GetFont(Fonts font)
	{
		switch (font)
		{
		case UIManager::Fonts::Title1:
			return titleFont1;
			break;
		case UIManager::Fonts::Title2:
			return titleFont2;
			break;
		case UIManager::Fonts::Default:
			return generalText;
			break;
		default:
			return generalText;
			break;
		}
	}

	void InitFonts()
	{
		titleFont1 = LoadFont("res/fonts/Blackout-Midnight.ttf");
		titleFont2 = LoadFont("res/fonts/AirAmerica-Regular.otf");
		generalText = LoadFont("res/fonts/Courier-Prime.ttf");
	}

	bool IsMouseOnButton(Button button)
	{
		return GetMouseX() > button.shape.x &&
			GetMouseY() > button.shape.y &&
			GetMouseX() < (button.shape.x + button.shape.width) &&
			GetMouseY() < (button.shape.y + button.shape.height);
	}

	void DrawButtonText(Button button, Color textColor, int fontSize)
	{
		DrawText(button.textShown.content.data(), static_cast<int>(button.shape.x) + static_cast<int>(button.shape.width / 2) - MeasureText(button.textShown.content.data(), fontSize) / 2, static_cast<int>(button.shape.y) + static_cast<int>(button.shape.height / 2) - fontSize / 2, fontSize, textColor);
	}

	void DrawButtonRect(Button button)
	{
		DrawRectangle(static_cast<int>(button.shape.x), static_cast<int>(button.shape.y), static_cast<int>(button.shape.width), static_cast<int>(button.shape.height), button.currentColor);
	}

	void PrintText(Text myText)
	{
		DrawTextEx(GetFont(myText.font), myText.content.data(), myText.location, static_cast<float>(myText.fontSize), textSpacing, myText.currentColor);
		//DrawText(myText.content.data(), static_cast<int>(myText.location.x), static_cast<int>(myText.location.y), myText.fontSize, myText.currentColor);
	}

	void PrintText(Text myText, int score)
	{
		DrawText(TextFormat(myText.content.data(), score), static_cast<int>(myText.location.x), static_cast<int>(myText.location.y), static_cast<int>(myText.fontSize), myText.currentColor); // PLAYER 1
	}

	Text GetText(float x, float y, Fonts font, int fontSize, string content, Color color)
	{
		Text myText;

		myText.currentColor = color;
		myText.content = content;
		myText.fontSize = fontSize;
		myText.location.x = x;
		myText.location.y = y;
		myText.font = font;

		return myText;
	}

	Text GetText(float x, float y, Fonts font, int fontSize, string content, Color color1, Color color2)
	{
		Text myText;

		myText.fontSize = fontSize;
		myText.alt1Color = color1;
		myText.alt2Color = color2;
		myText.currentColor = myText.alt1Color;
		myText.content = content;
		myText.location.x = x;
		myText.location.y = y;
		myText.font = font;

		return myText;
	}

	Button GetButton(float x, float y, float width, float height, string content, Color mainColor, Color highlightColor, Color textColor, Fonts font)
	{
		Button myButton;

		myButton.defaultColor = mainColor;
		myButton.currentColor = myButton.defaultColor;
		myButton.highlightColor = highlightColor;
		myButton.shape.width = width;
		myButton.shape.height = height;
		myButton.shape.x = x;
		myButton.shape.y = y;
		myButton.textShown.content = content;
		myButton.textShown.fontSize = static_cast<int>(height) / 2;
		myButton.textShown.currentColor = textColor;
		myButton.textShown.location.x = x + width / 2.0f - static_cast<float>(MeasureText(myButton.textShown.content.data(), myButton.textShown.fontSize), myButton.textShown.fontSize);
		myButton.textShown.font = font;

		return myButton;
	}
}

