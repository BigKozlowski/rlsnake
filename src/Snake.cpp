#include "Snake.hpp"
#include <cstdlib>
#include <iostream>
#include <format>

Snake::Snake(struct point head, struct point direction)
{
    this->length = 0;
    this->grow(head);
    this->direction = direction;
}

Snake::~Snake()
{
    std::free(this->body);
}

void Snake::grow(struct point p)
{
    struct point *a = (point *)std::realloc(this->body, sizeof(*this->body) * (this->length + 1));
    if (a)
    {
        this->body = a;
        this->body[this->length++] = p;
    }
}

void Snake::respawn()
{
    this->length = 0;
}

void Snake::draw(Texture2D texture, Texture2D headTexture)
{
    auto previousPoint = this->body[0];
    for (size_t i = 1; i < this->length; ++i)
    {
        if(this->body[i].x == previousPoint.x){
            DrawTextureEx(texture, Vector2{(float)this->body[i].x * 16, (float)this->body[i].y * 16 + 16}, 270.0, 1.0, WHITE);
        } else {
            DrawTexture(texture, this->body[i].x * 16, this->body[i].y * 16, WHITE);
        }
        previousPoint = this->body[i];
        // DrawRectangle(this->body[i].x * 16, this->body[i].y * 16, 16, 16, GRAY);
    }

    if(this->direction.x == 1) {
        DrawTextureEx(headTexture, Vector2{(float)this->body[0].x * 16 + 16, (float)this->body[0].y * 16 + 16}, 180.0, 1.0, WHITE);
    } else if (this->direction.x == -1) {
        DrawTextureEx(headTexture, Vector2{(float)this->body[0].x * 16, (float)this->body[0].y * 16}, 0.0, 1.0, WHITE);
    } else if (this->direction.y == 1) {
        DrawTextureEx(headTexture, Vector2{(float)this->body[0].x * 16, (float)this->body[0].y * 16 + 16}, 270.0, 1.0, WHITE);
    } else {
        DrawTextureEx(headTexture, Vector2{(float)this->body[0].x * 16 + 16, (float)this->body[0].y * 16}, 90.0, 1.0, WHITE);
    }
    // DrawRectangle(this->body[0].x * 16, this->body[0].y * 16, 16, 16, RED);
}

void Snake::setDirection(struct point p)
{
    this->direction = p;
}

void Snake::update()
{
    for (int i = (this->length) - 1; i > 0; i--)
    {
        this->body[i] = this->body[i - 1];
    }

    this->body[0].x = (this->body[0].x + this->direction.x) % 50;
    this->body[0].y = (this->body[0].y + this->direction.y) % 30;

    if (this->body[0].x < 0)
    {
        this->body[0].x = 49;
    }
    if (this->body[0].y < 0)
    {
        this->body[0].y = 29;
    }
}

bool Snake::isSelfCollided() {
    struct point head = this->body[0];
    for(int i = 1; i < this->length; i++) {
        if(this->body[i].x == head.x && this->body[i].y == head.y) {
            return true;
        }
    }
    return false;
}

bool Snake::hasToEatApple(Apple *apple) {
    if (this->body[0].x == apple->x && this->body[0].y == apple->y)
    {
        return true;
    }
    return false;
}

void Snake::eat(Apple *apple) {
    this->grow(apple->getPosition());
    apple->remove();
}

void Snake::changeDirection(struct point p)
{
    if (p.y != 0)
    {
        if (this->direction.y == 0)
        {
            this->direction = (struct point){0, p.y};
        }
    }
    else if (p.x != 0)
    {
        if (this->direction.x == 0)
        {
            this->direction = (struct point){p.x, 0};
        }
    }
}

struct point Snake::getHead()
{
    return this->body[0];
}

struct point Snake::getTail()
{
    return this->body[this->length - 1];
}