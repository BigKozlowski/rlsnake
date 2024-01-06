#include "Level.hpp"
#include <cstdlib>
#include <iostream>

Level::Level(char *filePath)
{
    if(FileExists(filePath)){
        int levelSize = 1530;
        auto contents = LoadFileData(filePath, &levelSize);
        
        for(int y = 0; y < 30; y++) {
            for(int x = 0; x < 50; x++) {
                std::cout << contents[y * x];
                this->walls[x][y] = contents[x + (y * 50)] == '0' ? false : true;
            }
        }
    }
}

Level::~Level()
{
}

void Level::draw(Texture2D wallTexture) {
    for(int y = 0; y < 30; y++) {
        for(int x = 0; x < 50; x++) {
            if(this->walls[x][y]){
                DrawTexture(wallTexture, x * 16, y * 16, WHITE);
            }
        }
    }
}