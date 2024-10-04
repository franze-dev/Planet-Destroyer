#include "UIManager.h"

bool UIManager::IsMouseOnButton(Button button)
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

void UIManager::DrawButtonText(Button button, Color textColor, int fontSize)
{
	DrawText(button.textShown.data(), button.shape.x + button.shape.width / 2 - MeasureText(button.textShown.data(), fontSize) / 2, button.shape.y + button.shape.height / 2 - fontSize / 2, fontSize, textColor);
}

void UIManager::DrawButtonRect(Button button)
{
	DrawRectangle(button.shape.x, button.shape.y, button.shape.width, button.shape.height, button.currentColor);
}

void UIManager::PrintText(Text myText)
{
	DrawText(myText.content.data(), myText.location.x, myText.location.y, myText.fontSize, myText.color);
}

void UIManager::PrintText(Text myText, int score)
{
	DrawText(TextFormat(myText.content.data(), score), myText.location.x, myText.location.y, myText.fontSize, myText.color); // PLAYER 1
}