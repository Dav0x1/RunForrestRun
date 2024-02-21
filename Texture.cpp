#include "Texture.h"

Colors Texture::ConvertToColor(int r, int g, int b)
{
    const int colorValues[16][3] = {
        {0, 0, 0},         // Czarny
        {0, 0, 128},       // Niebieski
        {0, 128, 0},       // Zielony
        {0, 128, 128},     // Cyjan
        {128, 0, 0},       // Czerwony
        {128, 0, 128},     // Magenta
        {128, 128, 0},     // Zolty
        {192, 192, 192},   // Bialy
        {128, 128, 128},   // Jasnoszary
        {0, 0, 255},       // Jasnoniebieski
        {0, 255, 0},       // Jasnozielony
        {0, 255, 255},     // Jasnocyjan
        {255, 0, 0},       // Jasnoczerwony
        {255, 0, 255},     // Jasnomagenta
        {255, 255, 0},     // Jasnozolty
        {255, 255, 255}    // Jasnobialy
    };

    Colors closestColor = Czarny;
    double minDistance = Distance(r, g, b, colorValues[Czarny][0], colorValues[Czarny][1], colorValues[Czarny][2]);

    for (int color = Czarny; color <= Jasnobialy; color++) {
        double distance = Distance(r, g, b, colorValues[color][0], colorValues[color][1], colorValues[color][2]);
        if (distance < minDistance) {
            minDistance = distance;
            closestColor = static_cast<Colors>(color);
        }
    }

    return closestColor;
}

double Texture::Distance(int r1, int g1, int b1, int r2, int g2, int b2)
{
    return std::sqrt((r1 - r2) * (r1 - r2) + (g1 - g2) * (g1 - g2) + (b1 - b2) * (b1 - b2));
}

Texture::Texture(std::vector<std::vector<Pixel>> &pixels)
{
    image.resize(pixels.size());
    for (int i = 0;i<pixels.size();i++) 
    {
        image[i].resize(pixels[i].size());
        for (int j = 0; j < pixels[i].size(); j++)
        {
            image[i][j] = ConvertToColor(pixels[i][j].r, pixels[i][j].g, pixels[i][j].b);
        }
    }
}