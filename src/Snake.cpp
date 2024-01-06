#include "Snake.hpp"
#include <cstdlib>

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

void Snake::draw(Texture2D texture, Texture2D headTexture, Texture2D angleTexture)
{
    auto previousPoint = this->body[0];
    for (size_t i = 1; i < this->length; ++i)
    {
        if(i == this->length - 1) {
            this->drawTail(texture, previousPoint, this->body[i]);
        } else {
            const auto nextPoint = this->body[i + 1];
            this->drawBodyPart(texture, angleTexture, previousPoint, this->body[i], nextPoint);
        }
        previousPoint = this->body[i];
    }

    this->drawHead(headTexture);
}

void Snake::drawBodyPart(Texture2D texture, Texture2D angleTexture, struct point prev, struct point curr, struct point next) {
    if(prev.x == next.x) {
        DrawTextureEx(texture, Vector2{(float)curr.x * 16, (float)curr.y * 16 + 16}, 270.0, 1.0, WHITE);
    } else if (prev.y == next.y) {
        DrawTexture(texture, curr.x * 16, curr.y * 16, WHITE);
    } else {
        this->drawSnakeAngle(angleTexture, prev, curr, next);
    }
}

void Snake::drawTail(Texture2D texture, struct point prev, struct point curr) {
    if (curr.x == prev.x)
    {
        DrawTextureEx(texture, Vector2{(float)curr.x * 16, (float)curr.y * 16 + 16}, 270.0, 1.0, WHITE);
    }
    else
    {
        DrawTexture(texture, curr.x * 16, curr.y * 16, WHITE);
    }
}

void Snake::drawSnakeAngle(Texture2D angleTexture, struct point prev, struct point curr, struct point next) {
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

bool Snake::isSelfCollided()
{
    struct point head = this->body[0];
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