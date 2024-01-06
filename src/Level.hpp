#pragma once
#include "main.hpp"

class Level
{
private:
    int wallsCount{};
public:
    bool walls[50][30]{};
    Level(char *filePath);
    ~Level();
    void draw(Texture2D wallTexture);
};
