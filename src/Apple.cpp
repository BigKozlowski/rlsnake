#include "Apple.hpp"

Apple::Apple(point position)
{
  this->x = position.x;
  this->y = position.y;
}

Apple::~Apple()
{
}

point Apple::getPosition()
{
  return point{this->x, this->y};
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
  }
}