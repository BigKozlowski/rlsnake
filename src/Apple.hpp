#pragma once
#include "main.hpp"

class Apple
{
private:
public:
  int16_t x;
  int16_t y;
  Apple(point position);
  ~Apple();
  void remove();
  point getPosition();
  void draw(Texture2D texture);
};
