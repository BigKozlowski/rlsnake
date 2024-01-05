#include "Engine.hpp"
#include <stdlib.h>
#include "raylib.h"

Engine::Engine()
{
  snake = new Snake({2, 0}, {0, 1});
  snake->grow({1, 0});
  apple = new Apple({-1, -1});
}

Engine::~Engine()
{
  delete snake;
}

void Engine::update()
{
  srand(frameCount);
  if (!isOnScreen(apple->getPosition()))
  {
    delete apple;
    apple = new Apple((struct point){(int16_t)(rand() % 50), (int16_t)(rand() % 30)});
  }
  frameCount++;
  handleKeypress();
  if (frameCount % 15 == 0)
  {
    snake->update(apple);
  }
}

void Engine::handleKeypress()
{
  int nowPressed = GetKeyPressed();
  lastPressed = nowPressed ? nowPressed : lastPressed;
  if (frameCount % 15 == 0)
  {
    if (lastPressed == (KEY_DOWN))
    {
      snake->changeDirection((struct point){0, 1});
    }
    if (lastPressed == (KEY_UP))
    {
      snake->changeDirection((struct point){0, -1});
    }
    if (lastPressed == (KEY_LEFT))
    {
      snake->changeDirection((struct point){-1, 0});
    }
    if (lastPressed == (KEY_RIGHT))
    {
      snake->changeDirection((struct point){1, 0});
    }
  }
}

void Engine::render()
{
  BeginDrawing();
  ClearBackground(BLACK);
  if (isOnScreen(apple->getPosition()))
  {
    DrawRectangle(apple->x * 16, apple->y * 16, 16, 16, GREEN);
  }
  snake->draw();
  EndDrawing();
}