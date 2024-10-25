#include "text.h"

namespace Text
{
	static Font titleFont1;
	static Font titleFont2;
	static Font generalText;

	void CenterTextX(Text& text)
	{
		text.location.x -= GetTextWidth(text) / 2;
	}

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
		case Fonts::Title1:
			return titleFont1;
			break;
		case Fonts::Title2:
			return titleFont2;
			break;
		case Fonts::Default:
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

	void UnloadFonts()
	{
		UnloadFont(GetFont(Fonts::Default));
		UnloadFont(GetFont(Fonts::Title1));
		UnloadFont(GetFont(Fonts::Title2));
	}

	void DrawText(Text myText)
	{
		SetTextureFilter(GetFont(myText.font).texture, TEXTURE_FILTER_BILINEAR);
		DrawTextEx(GetFont(myText.font), myText.content.data(), myText.location, static_cast<float>(myText.fontSize), textSpacing, myText.currentColor);
	}

	void DrawText(Text myText, int number)
	{
		SetTextureFilter(GetFont(myText.font).texture, TEXTURE_FILTER_BILINEAR);
		DrawTextEx(GetFont(myText.font), TextFormat(myText.content.data(), number), myText.location, static_cast<float>(myText.fontSize), textSpacing, myText.currentColor);
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
};