#include "Engine.hpp"
#include <stdlib.h>
#include <iostream>

void Engine::initializeSnake()
{
  this->snake = new Snake({2, 0}, {0, 1});
  this->snake->grow({1, 0});
  this->snake->grow({0, 0});
  this->snake->grow({-1, 0});
}

Engine::Engine()
{
  this->initializeSnake();
  this->apple = new Apple({-1, -1});
  this->gameRunning = true;

  Image appleImage = LoadImage("./assets/apple.png");
  Image snakeImage = LoadImage("./assets/snake_thin.png");
  Image mudImage = LoadImage("./assets/mud.png");
  Image headImage = LoadImage("./assets/snake_head.png");
  Image angleImage = LoadImage("./assets/snake_angle_thin.png");
  Image tailImage = LoadImage("./assets/snake_tail_thin.png");
  this->appleTexture = LoadTextureFromImage(appleImage);
  this->snakeBodyTexture = LoadTextureFromImage(snakeImage);
  this->mudTexture = LoadTextureFromImage(mudImage);
  this->snakeHeadTexture = LoadTextureFromImage(headImage);
  this->snakeAngleTexture = LoadTextureFromImage(angleImage);
  this->snakeTailTexture = LoadTextureFromImage(tailImage);
  UnloadImage(appleImage);
  UnloadImage(snakeImage);
  UnloadImage(mudImage);
  UnloadImage(headImage);
  UnloadImage(angleImage);
  UnloadImage(tailImage);
}

Engine::~Engine()
{
  delete snake;
  UnloadTexture(this->appleTexture);
  UnloadTexture(this->snakeBodyTexture);
  UnloadTexture(this->mudTexture);
  UnloadTexture(this->snakeHeadTexture);
  UnloadTexture(this->snakeAngleTexture);
}

void Engine::init()
{
  delete this->snake;
  this->initializeSnake();
  delete this->apple;
  this->apple = new Apple({-1, -1});
  this->gameRunning = true;
}


void Engine::update()
{
  srand(frameCount);
  if (!isOnScreen(apple->getPosition()))
  {
    delete apple;
    apple = new Apple(point{(int16_t)(rand() % 50), (int16_t)(rand() % 30)});
  }
  frameCount++;
  if (frameCount % 10 == 0)
  {
    snake->update();
    if (snake->isSelfCollided())
    {
      this->gameRunning = false;
    }
    if (snake->hasToEatApple(apple))
    {
      snake->eat(apple);
    }
  }
}

void Engine::handleKeypress()
{
  int nowPressed = GetKeyPressed();
  lastPressed = nowPressed ? nowPressed : lastPressed;
  if (frameCount % 10 == 0)
  {
    if (lastPressed == (KEY_DOWN))
    {
      snake->changeDirection(point{0, 1});
    }
    if (lastPressed == (KEY_UP))
    {
      snake->changeDirection(point{0, -1});
    }
    if (lastPressed == (KEY_LEFT))
    {
      snake->changeDirection(point{-1, 0});
    }
    if (lastPressed == (KEY_RIGHT))
    {
      snake->changeDirection(point{1, 0});
    }
    if (lastPressed == KEY_SPACE)
    {
      this->init();
      lastPressed = 0;
    }
  }
}

void Engine::render()
{
  switch (gameRunning)
  {
  case true:
  {

    BeginDrawing();
    DrawTextureQuad(mudTexture, Vector2{50, 30}, Vector2{0, 0}, Rectangle{0, 0, 800, 480}, WHITE);
    ClearBackground(BLACK);
    if (isOnScreen(apple->getPosition()))
    {
      apple[0].draw(appleTexture);
    }
    snake->draw(this->snakeBodyTexture, this->snakeHeadTexture, this->snakeAngleTexture, this->snakeTailTexture);
    EndDrawing();
  }
  break;
  default:
  {
    BeginDrawing();
    ClearBackground(RED);
    EndDrawing();
  }
  break;
  }
}