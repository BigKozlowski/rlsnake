#pragma once
#include "main.hpp"

class Apple
{
private:
public:
  int x;
  int y;
  Apple(point position);
  ~Apple();
  void remove();
  point getPosition();
  void draw(Texture2D texture);
};
