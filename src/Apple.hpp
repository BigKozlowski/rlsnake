#pragma once
#include <cstdint>

class Apple
{
public:
  int16_t x;
  int16_t y;
  Apple(struct point position);
  ~Apple();
  void remove();
  struct point getPosition();
  void draw();
};
