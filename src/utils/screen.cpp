#include "screen.hpp"
#include <cmath>

bool isOnScreen(point pos)
{
  return pos.x >= 0 && pos.y >= 0 && pos.x < 50 && pos.y < 30;
}

void DrawTextureQuad(Texture2D texture, Vector2 tiling, Vector2 offset, Rectangle quad, Color tint)
{
    Rectangle source = { offset.x*texture.width, offset.y*texture.height, tiling.x*texture.width, tiling.y*texture.height };
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(texture, source, quad, origin, 0.0f, tint);
}

double d2r(double d) {
  return (d / 180.0) * ((double) M_PI);
}

void DrawTextureRotatedInPlace(Texture2D texture, int x, int y, int size, float rotation) {
  if(rotation == 0.0) {
    DrawTexture(texture, x, y, WHITE);
  } else {
    const double rads = d2r(rotation);
    DrawTextureEx(texture, Vector2{(float)x * size + size * (float)std::cos(rads), (float)y * size - size * (float)std::sin(rads)}, rotation, 1.0, WHITE);
  }
}