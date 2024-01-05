#pragma once
#include "../main.hpp"

bool isOnScreen(struct point pos);
void DrawTextureQuad(Texture2D texture, Vector2 tiling, Vector2 offset, Rectangle quad, Color tint);