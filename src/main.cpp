#include "main.hpp"
#include "raylib.h"
#include <iostream>

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (480)

#define WINDOW_TITLE "My awesome snake"

int main()
{
    Engine *engine = new Engine();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        engine->handleKeypress();
        engine->update();
        engine->render();
    }

    return 0;
}