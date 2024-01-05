#include "screen.hpp"

bool isOnScreen(struct point pos)
{
  return pos.x >= 0 && pos.y >= 0 && pos.x < 50 && pos.y < 30;
}