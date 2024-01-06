#include "Snake.hpp"
#include <cstdlib>
#include <iostream>

Snake::Snake(point head, point direction)
{
    this->length = 0;
    this->grow(head);
    this->direction = direction;
}

Snake::~Snake()
{
    std::free(this->body);
}

void Snake::grow(point p)
{
    point *a = (point *)std::realloc(this->body, sizeof(*this->body) * (this->length + 1));
    if (a)
    {
        this->body = a;
        this->body[this->length++] = p;
    }
}

void Snake::draw(Texture2D texture, Texture2D headTexture, Texture2D angleTexture, Texture2D tailTexture)
{
    auto previousPoint = this->body[0];
    for (size_t i = 1; i < this->length; ++i)
    {
        if(i == this->length - 1) {
            this->drawTail(tailTexture, previousPoint, this->body[i]);
        } else {
            const auto nextPoint = this->body[i + 1];
            this->drawBodyPart(texture, angleTexture, previousPoint, this->body[i], nextPoint);
        }
        previousPoint = this->body[i];
    }

    this->drawHead(headTexture);
}

void Snake::drawBodyPart(Texture2D texture, Texture2D angleTexture, point prev, point curr, point next) {
    if(prev.x == next.x) {
        DrawTextureEx(texture, Vector2{(float)curr.x * 16, (float)curr.y * 16 + 16}, 270.0, 1.0, WHITE);
    } else if (prev.y == next.y) {
        DrawTexture(texture, curr.x * 16, curr.y * 16, WHITE);
    } else {
        this->drawSnakeAngle(angleTexture, prev, curr, next);
    }
}

void Snake::drawTail(Texture2D texture, point prev, point curr) {
    if(curr.x - prev.x > 1) {
        this->drawTail(texture, (point){curr.x + 1, prev.y}, curr);
        return;
    }
    if(curr.x - prev.x < -1) {
        this->drawTail(texture, (point){curr.x - 1, prev.y}, curr);
        return;
    }
    if(curr.y - prev.y > 1) {
        this->drawTail(texture, (point){prev.x, curr.y + 1}, curr);
        return;
    }
    if(curr.y - prev.y < -1) {
        this->drawTail(texture, (point){prev.x, curr.y - 1}, curr);
        return;
    }

    if (curr.y - prev.y < 0)
    {
        DrawTextureEx(texture, Vector2{(float)curr.x * 16, (float)curr.y * 16 + 16}, 270.0, 1.0, WHITE);
    }
    else if (curr.y - prev.y > 0) {
        DrawTextureEx(texture, Vector2{(float)curr.x * 16 + 16, (float)curr.y * 16}, 90.0, 1.0, WHITE);
    }
    else if (curr.x - prev.x < 0) {
        DrawTextureEx(texture, Vector2{(float)curr.x * 16 + 16, (float)curr.y * 16 + 16}, 180.0, 1.0, WHITE);
    }
    else
    {
        DrawTexture(texture, curr.x * 16, curr.y * 16, WHITE);
    }
}

void Snake::drawSnakeAngle(Texture2D angleTexture, point prev, point curr, point next) {
    if(curr.x - prev.x > 1) {
        this->drawSnakeAngle(angleTexture, (point){curr.x + 1, prev.y}, curr, next);
        return;
    }
    if(curr.x - prev.x < -1) {
        this->drawSnakeAngle(angleTexture, (point){curr.x - 1, prev.y}, curr, next);
        return;
    }
    if(curr.y - prev.y > 1) {
        this->drawSnakeAngle(angleTexture, (point){prev.x, curr.y + 1}, curr, next);
        return;
    }
    if(curr.y - prev.y < -1) {
        this->drawSnakeAngle(angleTexture, (point){prev.x, curr.y - 1}, curr, next);
        return;
    }

    if(curr.x - next.x > 1) {
        this->drawSnakeAngle(angleTexture, prev, curr, (point){curr.x + 1, next.y});
        return;
    }
    if(curr.x - next.x < -1) {
        this->drawSnakeAngle(angleTexture, prev, curr, (point){curr.x - 1, next.y});
        return;
    }
    if(curr.y - next.y > 1) {
        this->drawSnakeAngle(angleTexture, prev, curr, (point){next.x, curr.y + 1});
        return;
    }
    if(curr.y - next.y < -1) {
        this->drawSnakeAngle(angleTexture, prev, curr, (point){next.x, curr.y - 1});
        return;
    }

    if(curr.x == next.x) {
        if(prev.x < next.x && prev.y < next.y) {
            DrawTextureEx(angleTexture, Vector2{(float)curr.x * 16 + 16, (float)curr.y * 16 + 16}, 180.0, 1.0, WHITE);
        } else if (prev.x < next.x && prev.y > next.y) {
            DrawTextureEx(angleTexture, Vector2{(float)curr.x * 16, (float)curr.y * 16 + 16}, 270.0, 1.0, WHITE);//correct
        } else if (prev.x > next.x && prev.y < next.y) {
            DrawTextureEx(angleTexture, Vector2{(float)curr.x * 16 + 16, (float)curr.y * 16}, 90.0, 1.0, WHITE);//correct
        } else {
            DrawTexture(angleTexture, curr.x * 16, curr.y * 16, WHITE); //correct
        }
    } else {
        if(prev.x < next.x && prev.y < next.y) {
            DrawTexture(angleTexture, curr.x * 16, curr.y * 16, WHITE); //correct
        } else if (prev.x < next.x && prev.y > next.y) {
            DrawTextureEx(angleTexture, Vector2{(float)curr.x * 16 + 16, (float)curr.y * 16}, 90.0, 1.0, WHITE); //correct 
        } else if (prev.x > next.x && prev.y < next.y) {
            DrawTextureEx(angleTexture, Vector2{(float)curr.x * 16, (float)curr.y * 16 + 16}, 270.0, 1.0, WHITE); //correct
        } else {
            DrawTextureEx(angleTexture, Vector2{(float)curr.x * 16 + 16, (float)curr.y * 16 + 16}, 180.0, 1.0, WHITE); // correct
        }
    }
}

void Snake::drawHead(Texture2D headTexture) {
    if (this->direction.x == 1)
    {
        DrawTextureEx(headTexture, Vector2{(float)this->body[0].x * 16 + 16, (float)this->body[0].y * 16 + 16}, 180.0, 1.0, WHITE);
    }
    else if (this->direction.x == -1)
    {
        DrawTextureEx(headTexture, Vector2{(float)this->body[0].x * 16, (float)this->body[0].y * 16}, 0.0, 1.0, WHITE);
    }
    else if (this->direction.y == 1)
    {
        DrawTextureEx(headTexture, Vector2{(float)this->body[0].x * 16, (float)this->body[0].y * 16 + 16}, 270.0, 1.0, WHITE);
    }
    else
    {
        DrawTextureEx(headTexture, Vector2{(float)this->body[0].x * 16 + 16, (float)this->body[0].y * 16}, 90.0, 1.0, WHITE);
    }
}

void Snake::setDirection(point p)
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

bool Snake::isSelfCollided()
{
    point head = this->body[0];
    for (int i = 1; i < this->length; i++)
    {
        if (this->body[i].x == head.x && this->body[i].y == head.y)
        {
            return true;
        }
    }
    return false;
}

bool Snake::hasToEatApple(Apple *apple)
{
    if (this->body[0].x == apple->x && this->body[0].y == apple->y)
    {
        return true;
    }
    return false;
}

void Snake::eat(Apple *apple)
{
    this->grow(apple->getPosition());
    apple->remove();
}

void Snake::changeDirection(point p)
{
    if (p.y != 0)
    {
        if (this->direction.y == 0)
        {
            this->direction = point{0, p.y};
        }
    }
    else if (p.x != 0)
    {
        if (this->direction.x == 0)
        {
            this->direction = point{p.x, 0};
        }
    }
}

point Snake::getHead()
{
    return this->body[0];
}

point Snake::getTail()
{
    return this->body[this->length - 1];
}