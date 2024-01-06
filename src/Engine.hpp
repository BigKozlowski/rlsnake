#pragma once
#include "main.hpp"

class Snake;

class Engine
{
private:
  Snake *snake;
  uint32_t frameCount;
  Apple *apple;
  int lastPressed;
  void initializeSnake();
  Texture2D appleTexture{};
  Texture2D snakeBodyTexture{};
  Texture2D mudTexture{};
  Texture2D snakeHeadTexture{};
  Texture2D snakeAngleTexture{};
  Texture2D snakeTailTexture{};
  uint32_t applesEaten{};
  uint32_t difficultyLevel{1};
  uint32_t score{};
  /* data */
public:
  Engine(/* args */);
  ~Engine();
  void handleKeypress();
  void init();
  void update();
  void render();
  bool gameRunning;
};