#include "Apple.hpp"
#include "utils/screen.hpp"
#include <iostream>

Apple::Apple(struct point position, const char *texturePath)
{
  this->x = position.x;
  this->y = position.y;
  // this->image = LoadImage(texturePath);
  // std::cout << "test" << std::endl;
  // this->texture = LoadTextureFromImage(this->image);
}

Apple::~Apple()
{
  // UnloadTexture(texture);
  // UnloadImage(image);
}

struct point Apple::getPosition()
{
  return (struct point){this->x, this->y};
}

void Apple::remove()
{
  this->x = -1;
  this->y = -1;
}

void Apple::draw(Texture2D texture)
{
  if (isOnScreen(this->getPosition()))
  {
    DrawTexture(texture, this->x * 16, this->y * 16, WHITE);
    // DrawRectangle(this->x * 16, this->y * 16, 16, 16, GREEN);
  }
}