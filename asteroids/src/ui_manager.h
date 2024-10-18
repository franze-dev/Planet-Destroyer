#pragma once

#include <iostream>
#include "raylib.h"

#include "scene_manager.h"

using namespace std;

namespace UIManager
{
	const float textSpacing = 20.0f;

	enum class FontSize
	{
		small = 20,
		medium = 40,
		big = 80,
		giant = 140
	};

	enum class Fonts
	{
		Title1,
		Title2,
		Default
	};

	enum class Padding
	{
		small = 20,
		medium = 60,
		big = 90
	};

	struct Text
	{
		string content = " ";
		int fontSize = 0;
		Vector2 location;
		Color currentColor;
		Color alt1Color;
		Color alt2Color;
		Fonts font;
	};

	//Prints a text
	void PrintText(Text myText);
	//Prints a text that needs a number to print
	void PrintText(Text myText, int score);
	
	struct Button
	{
		Rectangle shape;
		Text textShown;
		Color defaultColor;
		Color altColor;
		Color currentColor;
		//This is the color when the user hovers the mouse over the button.
		Color highlightColor;
	};

	float GetTextWidth(Text text);
	float GetTextHeight(Text text);
	Font GetFont(Fonts font);
	void InitFonts();
	//Detects the mouse inside the bounds of a button
	bool IsMouseOnButton(Button button);
	void CheckSceneChange(Button& button, SceneManager::Scene scene);
	void DrawButton(Button button);
	//Create texts
	Text GetText(float x, float y, Fonts font, int fontSize, string content, Color color);
	//If the text is the same and only the color changes at one point, then this is used.
	//color1 is the current color.
	Text GetText(float x, float y, Fonts font, int fontSize, string content, Color color1, Color color2);
	//Create buttons
	Button GetButton(float x, float y, float width, float height, string content, Color mainColor, Color highlightColor, Color textColor, Fonts font);
}

