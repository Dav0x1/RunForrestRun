// Library
#include "LoadingScreen.h"
#include "BmpReader.h"
// Preprocessor directive
#define WIDTH 230
#define HEIGHT 125
// Functions
void loadTextures(std::map<std::string, Texture>& textures) {
    BmpReader bmpReader;
    std::vector<std::vector<Pixel>> pixelsArray;

    bmpReader.load("assets/chars.bmp", pixelsArray);
    Texture image1(pixelsArray);
    textures["CHARS"] = image1;
    
    bmpReader.load("assets/player.bmp", pixelsArray);
    Texture image2(pixelsArray);
    textures["PLAYER"] = image2;

    bmpReader.load("assets/background.bmp", pixelsArray);
    Texture image3(pixelsArray);
    textures["BACKGROUND"] = image3;

    bmpReader.load("assets/bat.bmp", pixelsArray);
    Texture image4(pixelsArray);
    textures["BAT"] = image4;
}
int setConsoleWindowParameters(HWND& consolHWND, HANDLE& consoleHANDLE, int width, int height,int fontw,int fonth)
{
    if (consolHWND == INVALID_HANDLE_VALUE) {
        std::cout << "ERROR:INVALID_HANDLE_VALUE";
        return -1;
    }

    SetConsoleTitle(L"Run Forrest Run");

    SMALL_RECT m_rectWindow = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(consolHWND, TRUE, &m_rectWindow);

    // Resize screen buffer
    COORD coord = { (short)width, (short)height };
    if (!SetConsoleScreenBufferSize(consolHWND, coord)) {
        std::cout << "ERROR:SetConsoleScrnBufferSize";
        return -1;
    }
    // Assign screen buffer to the console
    if (!SetConsoleActiveScreenBuffer(consolHWND)) {
        std::cout << "ERROR:SetConsoleActiveScreenBuffer";
        return -1;
    }

    // Set the font size now that the screen buffer has been assigned to the console
    CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = (SHORT)fontw;
        cfi.dwFontSize.Y = (SHORT)fonth;
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;

    wcscpy_s(cfi.FaceName, L"Consolas");
    if (!SetCurrentConsoleFontEx(consolHWND, false, &cfi)) {
        std::cout << "ERROR:SetCurrentConsoleFontEx";
        return -1;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(consolHWND, &csbi)) {
        std::cout << "ERROR:GetConsoleScreenBufferInfo";
        return -1;
    }
    if (fonth > csbi.dwMaximumWindowSize.Y) {
        std::cout << "ERROR:Font height too big";
        return -1;
    }
    if (fontw > csbi.dwMaximumWindowSize.X) {
        std::cout << "ERROR:Font width too big";
        return -1;
    }

    // Set Physical Console Window Size
    m_rectWindow = { 0, 0, short(width -1), short(height - 1) };
    if (!SetConsoleWindowInfo(consolHWND, TRUE, &m_rectWindow)) {
        std::cout << "ERROR:SetConsoleWindowInfo";
        return -1;
    }

    // Set flags to allow mouse input		
    if (!SetConsoleMode(consoleHANDLE, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT)) {
        std::cout << "ERROR:SetConsoleMode";
        return -1;
    }
    return 1;
}
// Main function
int main() {
    StateData stateData;
    // State data initialization
    stateData.consoleHWND = GetConsoleWindow();
    stateData.consoleHANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

    stateData.lastDisplay = new char* [HEIGHT];
    stateData.display = new char* [WIDTH];
    for (size_t i = 0; i < HEIGHT; i++)
    {
        stateData.lastDisplay[i] = new char[WIDTH];
        stateData.display[i] = new char[WIDTH];

        for (size_t j = 0; j < WIDTH; j++)
        {
            stateData.lastDisplay[i][j] = Colors::Czarny;
            stateData.display[i][j] = Colors::Czarny;
        }
    }

    stateData.width = WIDTH;
    stateData.height = HEIGHT;

    loadTextures(stateData.textures);
    stateData.states.push(new LoadingScreen(stateData));

    setConsoleWindowParameters(stateData.consoleHWND, stateData.consoleHANDLE,WIDTH,HEIGHT,8,8);
    // main loop
    while (!stateData.isExit)
    {
        stateData.states.top()->update();
        stateData.states.top()->render();
    }

    return 0;
}