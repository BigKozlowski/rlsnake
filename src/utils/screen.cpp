#include "screen.hpp"

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