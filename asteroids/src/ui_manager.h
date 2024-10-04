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
		Color color;
	};

	//Prints a text
	void PrintText(Text myText);
	//Prints a text that needs a number to print (used specifically for printing the score of the players)
	void PrintText(Text myText, int score);
	
	struct Button
	{
		Rectangle shape;
		string textShown;
		//If there are two texts possibilities in the same button, these are the two alternatives.
		string textAlt1;
		string textAlt2;
		Color defaultColor;
		//If the button is a switch, it's convenient for it to have two colors that differenciate the 
		//status in which theyre in (on or off). I distinguish that with "defaultColor" and "secondDefaultColor"
		Color secondDefaultColor;
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
}

