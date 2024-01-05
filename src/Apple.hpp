#pragma once
#include <cstdint>
#include <raylib.h>

class Apple
{
private:
  Texture2D texture{};
  Image image{};
public:
  int16_t x;
  int16_t y;
  Apple(struct point position, const char *texturePath);
  ~Apple();
  void remove();
  struct point getPosition();
  void draw(Texture2D texture);
};
