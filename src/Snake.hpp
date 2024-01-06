#pragma once
#include "main.hpp"

class Apple;

class Snake
{
private:
    point *body{};
    point direction;
    uint16_t length;
    void drawSnakeAngle(Texture2D angleTexture, point prev, point curr, point next);
    void drawTail(Texture2D texture, point prev, point curr);
    void drawBodyPart(Texture2D texture, Texture2D angleTexture, point prev, point curr, point next);
    void drawHead(Texture2D headTexture);
    
public:
    Snake(point head, point direction);
    ~Snake();
    void grow(point p);
    void draw(Texture2D texture, Texture2D headTexture, Texture2D angleTexture);
    void setDirection(point p);
    void update();
    void changeDirection(point p);
    point getHead();
    point getTail();
    bool hasToEatApple(Apple *apple);
    bool isSelfCollided();
    void eat(Apple *apple);
};