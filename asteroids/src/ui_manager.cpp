#include "UI_Manager.h"

namespace UIManager
{
	bool IsMouseOnButton(Button button)
	{
		if (GetMouseX() > button.shape.x &&
			GetMouseY() > button.shape.y &&
			GetMouseX() < (button.shape.x + button.shape.width) &&
			GetMouseY() < (button.shape.y + button.shape.height))
		{
			return true;
		}
		return false;
	}

	void DrawButtonText(Button button, Color textColor, int fontSize)
	{
		DrawText(button.textShown.content.data(), static_cast<int>(button.shape.x) + static_cast<int>(button.shape.width / 2) - MeasureText(button.textShown.content.data(), fontSize) / 2, static_cast<int>(button.shape.y) + static_cast<int>(button.shape.height / 2) - fontSize / 2, fontSize, textColor);
	}

	void DrawButtonRect(Button button)
	{
		DrawRectangle(button.shape.x, button.shape.y, button.shape.width, button.shape.height, button.currentColor);
	}

	void PrintText(Text myText)
	{
		DrawText(myText.content.data(), myText.location.x, myText.location.y, myText.fontSize, myText.currentColor);
	}

	void PrintText(Text myText, int score)
	{
		DrawText(TextFormat(myText.content.data(), score), myText.location.x, myText.location.y, myText.fontSize, myText.currentColor); // PLAYER 1
	}

	Text GetText(float x, float y, int fontSize, string content, Color color)
	{
		Text myText;

		myText.currentColor = color;
		myText.content = content;
		myText.fontSize = fontSize;
		myText.location.x = x;
		myText.location.y = y;

		return myText;
	}

	Text GetText(float x, float y, int fontSize, string content, Color color1, Color color2)
	{
		Text myText;

		myText.fontSize = fontSize;
		myText.alt1Color = color1;
		myText.alt2Color = color2;
		myText.currentColor = myText.alt1Color;
		myText.content = content;
		myText.location.x = x;
		myText.location.y = y;

		return myText;
	}

	Button GetButton(float x, float y, int width, int height, string content, Color mainColor, Color highlightColor, Color textColor)
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
		myButton.textShown.fontSize = height / 2;
		myButton.textShown.currentColor = textColor;
		myButton.textShown.location.x = x + width / 2.0f - static_cast<float>(MeasureText(myButton.textShown.content.data(), myButton.textShown.fontSize), myButton.textShown.fontSize);

		return myButton;
	}
}

