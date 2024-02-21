#include "BmpReader.h"

bool BmpReader::load(const std::string & filePath, std::vector<std::vector<Pixel>>& pixels)
{
    char type[2];
    uint32_t offset = 0;
    uint32_t width = 0;
    uint32_t height = 0;

    char pixelData = 0;
    // Load file
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return 0; // Error while loading file
    
    // Reading file type
    file.read(type, sizeof(type));
    if (type[0] != 'B' || type[1] != 'M') return 0; // Error diffrent file type

    // Reading offset
    file.seekg(10, std::ios::beg);
    file.read(reinterpret_cast<char*>(&offset), sizeof(offset));

    // Reading width and height
    file.seekg(18, std::ios::beg);
    file.read(reinterpret_cast<char*>(&width), sizeof(width));
    file.read(reinterpret_cast<char*>(&height), sizeof(height));
        
    // Reading pixels
    file.seekg(offset, std::ios::beg);
    pixels.resize(height);

    int rowSize = ((width * 3 + 3) / 4) * 4;
    for (int i = height - 1; i >= 0; i--) {
        pixels[i].resize(width);
        for (int j = 0; j < width; j++) {
            file.read(reinterpret_cast<char*>(&pixels[i][j]), sizeof(Pixel));
        }
        // Skip padding
        for (int k = width * 3; k < rowSize; k++) {
            file.read(&pixelData, sizeof(pixelData));
        }
    }
    file.close();

    return 1;
}