#pragma once
#include <iostream>
#include "raylib.h"
using namespace std;

namespace UIManager
{
	struct Text
	{
		string content = " ";
		int fontSize = 0;
		Vector2 location;
		Color currentColor;
		Color alt1Color;
		Color alt2Color;
	};

	//Prints a text
	void PrintText(Text myText);
	//Prints a text that needs a number to print (used specifically for printing the score of the players)
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

	//Detects the mouse inside the bounds of a button
	bool IsMouseOnButton(Button button);
	//Draws the text in a button, as well as automatically centering it.
	void DrawButtonText(Button button, Color color, int fontSize);
	//Draws the square of the button
	void DrawButtonRect(Button button);
	//Create texts
	Text GetText(float x, float y, int fontSize, string content, Color color);
	//If the text is the same and only the color changes at one point, then this is used.
	//color1 is the current color.
	Text GetText(float x, float y, int fontSize, string content, Color color1, Color color2);
	//Create buttons
	Button GetButton(float x, float y, float width, float height, string content, Color mainColor, Color highlightColor, Color textColor);

}

