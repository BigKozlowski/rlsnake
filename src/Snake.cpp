#include "Snake.hpp"
#include <cstdlib>
#include <raylib.h>
#include <iostream>
#include <format>

Snake::Snake(struct point head, struct point direction)
{
    this->length = 1;
    this->grow(head);
    this->direction = direction;
}

Snake::~Snake()
{
    delete this->body;
}

void Snake::grow(struct point p)
{
    struct point *a = (point *)std::realloc(this->body, sizeof *body * (this->length + 1));
    if (a)
    {
        this->body = a;
        this->body[this->length++] = p;
    }
}

void Snake::draw()
{
    for (size_t i = 0; i < this->length; ++i)
    {
        DrawRectangle(this->body[i].x * 16, this->body[i].y * 16, 16, 16, GRAY);
    }

    DrawRectangle(this->body[0].x * 16, this->body[0].y * 16, 16, 16, RED);
}

void Snake::setDirection(struct point p)
{
    this->direction = p;
}

void Snake::update(Apple *apple)
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

    if (this->body[0].x == apple->x && this->body[0].y == apple->y)
    {
        this->grow(apple->getPosition());
        std::cout << "EATEN" << std::endl;
        apple->remove();
    }
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