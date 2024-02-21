#include "Text.h"

Text::Text(int x, int y, int letterWidth, int letterHeight, std::string text, Texture& texture):
	x(x),y(y),letterWidth(letterWidth),letterHeight(letterHeight),text(text), texture(texture)
{
}
