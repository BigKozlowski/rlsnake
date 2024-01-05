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
  void handleKeypress();
  /* data */
public:
  Engine(/* args */);
  ~Engine();
  void init();
  void update();
  void render();
};