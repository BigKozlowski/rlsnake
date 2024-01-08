#pragma once
#include "../main.hpp"

bool isOnScreen(point pos);
void DrawTextureQuad(Texture2D texture, Vector2 tiling, Vector2 offset, Rectangle quad, Color tint);
void DrawTextureRotatedInPlace(Texture2D texture, int x, int y, int size, float rotation);