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