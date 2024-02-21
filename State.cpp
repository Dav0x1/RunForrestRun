#include "State.h"

State::State(StateData& stateData)
	:stateData(stateData)
{
}

State::~State()
{
	;
}

void State::updateDeltaTime()
{
	auto currentTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> deltaTime = currentTime - this->startTime;
	this->dtTime = deltaTime.count();

	this->startTime = currentTime;
}

void State::displayPixel(Colors color,SHORT x, SHORT y)
{
	COORD position = {x,y};
	DWORD charsWritten = 0;
	WORD attribute = color;
	wchar_t moj_wchar = L'\u2588'; //White square
	WriteConsoleOutputAttribute(stateData.consoleHANDLE, &attribute, 1, position, &charsWritten);
	WriteConsoleOutputCharacter(stateData.consoleHANDLE, &moj_wchar, 1, position, &charsWritten);
}

void State::clearDisplay()
{
	for (size_t i = 0; i < stateData.height; i++)
	{
		for (size_t j = 0; j < stateData.width; j++)
		{
			stateData.display[i][j] = Colors::Czarny;
		}
	}
}

void State::display()
{
	for (size_t i = 0; i < stateData.height; i++)
	{
		for (size_t j = 0; j < stateData.width;j++) {
			if (stateData.display[i][j] != stateData.lastDisplay[i][j])
			{
				// update display array
				stateData.lastDisplay[i][j] = stateData.display[i][j];
				// display char
				displayPixel(Colors(stateData.display[i][j]),j,i);
			}
		}
	}
}

void State::displaySprite(Sprite& sprite)
{
	// Make sure that we don't draw out of display
	if (sprite.x + sprite.width <= stateData.width && sprite.y + sprite.height <= stateData.height) {

		for (size_t i = 0; i < sprite.height; i++)
		{
			for (size_t j = 0; j < sprite.width; j++) {
				if (sprite.image->image[sprite.frameY + i][sprite.frameX + j] != Colors::Czarny)
				stateData.display[sprite.y + i][sprite.x + j] = sprite.image->image[sprite.frameY + i][sprite.frameX + j];
			}
		}
	}
}

void State::displayText(Text& text)
{
	for (int x = 0;x<text.text.size();x++) {
		// Letters A-Z
		if (text.text[x]>96 && text.text[x]<123) {
			// Make sure that we don't draw out of display
			if (text.x + text.letterWidth < stateData.width && text.y + text.letterHeight < stateData.height) {

				for (size_t i = 0; i < text.letterHeight; i++)
				{
					for (size_t j = 0; j < text.letterWidth; j++) {
						if(text.texture.image[i][(text.letterWidth) * (text.text[x] - 97) + j] != Colors::Czarny)
							stateData.display[text.y + i][text.x + j + (x*text.letterWidth)] = text.texture.image[i][(text.letterWidth)* (text.text[x]-97) + j];
						else if(text.isActive) {
							stateData.display[text.y + i][text.x + j + (x * text.letterWidth)] = text.texture.image[i][(text.letterWidth) * (text.text[x] - 97) + j];
						}
					}
				}
			}
		}
		else if (text.text[x] > 48 && text.text[x] < 58) {
			// Make sure that we don't draw out of display
			if (text.x + text.letterWidth < stateData.width && text.y + text.letterHeight < stateData.height) {

				for (size_t i = 0; i < text.letterHeight; i++)
				{
					for (size_t j = 0; j < text.letterWidth; j++) {
						if (text.texture.image[i + text.letterHeight + 1][(text.letterWidth) * (text.text[x] - 49) + j] != Colors::Czarny)
							stateData.display[text.y + i][text.x + j + (x * text.letterWidth)] = text.texture.image[i + text.letterHeight + 1][(text.letterWidth) * (text.text[x] - 49) + j];
						else if (text.isActive) {
							stateData.display[text.y + i][text.x + j + (x * text.letterWidth)] = text.texture.image[i + text.letterHeight + 1][(text.letterWidth) * (text.text[x] - 49) + j];
						}
					}
				}
			}
		}
	}
}

void State::displayRectangle(Rectanglee& rect)
{
	// Make sure that we don't draw out of display
	if (rect.x + rect.width < stateData.width && rect.y + rect.height < stateData.height) {

		for (size_t i = 0; i < rect.height; i++)
		{
			for (size_t j = 0; j < rect.width; j++) {
				stateData.display[rect.y + i][rect.x + j] = rect.color;
			}
		}
	}
}
