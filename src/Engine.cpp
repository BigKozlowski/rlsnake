#include "Engine.hpp"
#include <stdlib.h>
#include <iostream>

void Engine::initializeSnake() {
  this->snake = new Snake({2, 0}, {0, 1});
  this->snake->grow({1, 0});
  this->snake->grow({0, 0});
  this->snake->grow({-1, 0});
}

Engine::Engine()
{
  this->initializeSnake();
  this->apple = new Apple({-1, -1}, "./src/apple.png");
  this->gameRunning = true;
}

void Engine::init() {
  delete this->snake;
  this->initializeSnake();
  delete this->apple;
  this->apple = new Apple({-1, -1}, "./apple.png");
  this->gameRunning = true;
}

Engine::~Engine()
{
  delete snake;
}

void Engine::update()
{
  srand(frameCount);
  if (!isOnScreen(apple->getPosition()))
  {
    delete apple;
    apple = new Apple((struct point){(int16_t)(rand() % 50), (int16_t)(rand() % 30)}, "./apple.png");
  }
  frameCount++;
  if (frameCount % 10 == 0)
  {
    snake->update();
    if(snake->isSelfCollided()){
      this->gameRunning = false;
    }
    if(snake->hasToEatApple(apple)){
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
      snake->changeDirection((struct point){0, 1});
    }
    if (lastPressed == (KEY_UP))
    {
      snake->changeDirection((struct point){0, -1});
    }
    if (lastPressed == (KEY_LEFT))
    {
      snake->changeDirection((struct point){-1, 0});
    }
    if (lastPressed == (KEY_RIGHT))
    {
      snake->changeDirection((struct point){1, 0});
    }
    if (lastPressed == KEY_SPACE) {
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
      const auto image = LoadImage("./src/apple.png");
      const auto texture = LoadTextureFromImage(image);
      const auto snakeImage = LoadImage("./src/snake.png");
      const auto snakeTexture = LoadTextureFromImage(snakeImage);
      const auto mudImage = LoadImage("./src/mud.png");
      const auto mudTexture = LoadTextureFromImage(mudImage);
      const auto headImage = LoadImage("./src/snake_head.png");
      const auto headTexture = LoadTextureFromImage(headImage);
      BeginDrawing();
      DrawTextureQuad(mudTexture, Vector2{50, 30}, Vector2{0, 0}, Rectangle{0, 0, 800, 480}, WHITE);
      ClearBackground(BLACK);
      if (isOnScreen(apple->getPosition()))
      {
        apple->draw(texture);
      }
      snake->draw(snakeTexture, headTexture);
      EndDrawing();
      UnloadTexture(texture);
      UnloadImage(image);
      UnloadTexture(snakeTexture);
      UnloadImage(snakeImage);
      UnloadTexture(mudTexture);
      UnloadImage(mudImage);
      UnloadTexture(headTexture);
      UnloadTexture(headTexture);
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