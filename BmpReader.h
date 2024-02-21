#pragma once
#include <string>
#include <fstream>
#include "Texture.h"


class BmpReader
{
public:
	// Return value:
	// 0 - failed | 1 - success
	bool load(const std::string &fileName, std::vector<std::vector<Pixel>> &pixels);
};