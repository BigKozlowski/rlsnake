#pragma once
#include "main.hpp"

class Apple;

class Snake
{
private:
    struct point *body{};
    struct point direction;
    uint16_t length;
    void drawSnakeAngle(Texture2D angleTexture, struct point prev, struct point curr, struct point next);
    void drawTail(Texture2D texture, struct point prev, struct point curr);
    void drawBodyPart(Texture2D texture, Texture2D angleTexture, struct point prev, struct point curr, struct point next);
    void drawHead(Texture2D headTexture);
    
public:
    Snake(struct point head, struct point direction);
    ~Snake();
    void grow(struct point p);
    void draw(Texture2D texture, Texture2D headTexture, Texture2D angleTexture);
    void setDirection(struct point p);
    void update();
    void changeDirection(struct point p);
    struct point getHead();
    struct point getTail();
    bool hasToEatApple(Apple *apple);
    bool isSelfCollided();
    void eat(Apple *apple);
};