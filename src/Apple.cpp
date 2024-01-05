#include "Apple.hpp"
#include "raylib.h"
#include "utils/screen.hpp"

Apple::Apple(struct point position)
{
  this->x = position.x;
  this->y = position.y;
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

void Apple::draw()
{
  if (isOnScreen(this->getPosition()))
  {
    DrawRectangle(this->x * 16, this->y * 16, 16, 16, GREEN);
  }
}

Apple::~Apple()
{
}