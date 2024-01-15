#include "Engine.hpp"
#include <stdlib.h>
#include <iostream>

void Engine::initializeSnake()
{
  this->snake = new Snake({4, 1}, {1, 0});
  this->snake->grow({3, 1});
  this->snake->grow({2, 1});
}

Engine::Engine()
{
  this->initializeSnake();
  this->apple = new Apple({-1, -1});
  this->level = new Level((char *)"./assets/maze.lev");
  this->mode = GAME;

  Image appleImage = LoadImage("./assets/apple.png");
  Image snakeImage = LoadImage("./assets/snake_thin.png");
  Image mudImage = LoadImage("./assets/mud.png");
  Image headImage = LoadImage("./assets/snake_head.png");
  Image angleImage = LoadImage("./assets/snake_angle_thin.png");
  Image tailImage = LoadImage("./assets/snake_tail_thin.png");
  Image wallImage = LoadImage("./assets/wall.png");
  this->appleTexture = LoadTextureFromImage(appleImage);
  this->snakeBodyTexture = LoadTextureFromImage(snakeImage);
  this->mudTexture = LoadTextureFromImage(mudImage);
  this->snakeHeadTexture = LoadTextureFromImage(headImage);
  this->snakeAngleTexture = LoadTextureFromImage(angleImage);
  this->snakeTailTexture = LoadTextureFromImage(tailImage);
  this->wallTexture = LoadTextureFromImage(wallImage);
  UnloadImage(appleImage);
  UnloadImage(snakeImage);
  UnloadImage(mudImage);
  UnloadImage(headImage);
  UnloadImage(angleImage);
  UnloadImage(tailImage);
  UnloadImage(wallImage);
}

Engine::~Engine()
{
  delete snake;
  UnloadTexture(this->appleTexture);
  UnloadTexture(this->snakeBodyTexture);
  UnloadTexture(this->mudTexture);
  UnloadTexture(this->snakeHeadTexture);
  UnloadTexture(this->snakeAngleTexture);
  UnloadTexture(this->snakeTailTexture);
  UnloadTexture(this->wallTexture);
}

void Engine::init()
{
  delete this->snake;
  this->initializeSnake();
  delete this->apple;
  this->apple = new Apple({-1, -1});
  this->mode = GAME;
  this->score = 0;
  this->applesEaten = 0;
  this->difficultyLevel = 1;
  this->lastTickTime = GetTime();
  this->snakeDirection = point{0, 0};
}

void Engine::tick()
{
  srand((unsigned int)GetTime() * 1000.0);
  if (!isOnScreen(apple->getPosition()))
  {
    delete apple;
    apple = new Apple(point{(int16_t)(rand() % 50), (int16_t)(rand() % 30)});
    while (this->level->walls[this->apple->getPosition().x][this->apple->getPosition().y])
    {
      delete apple;
      apple = new Apple(point{(int16_t)(rand() % 50), (int16_t)(rand() % 30)});
    }
  }
  // if (frameCount % (16 - this->difficultyLevel) == 0)
  {
    snake->changeDirection(this->snakeDirection);
    snake->update();
    if (snake->isSelfCollided())
    {
      this->mode = GAMEOVER;
    }
    if (this->level->walls[snake->getHead().x][snake->getHead().y])
    {
      this->mode = GAMEOVER;
    }
    if (snake->hasToEatApple(apple))
    {
      snake->eat(apple);
      this->applesEaten++;
      this->score += this->difficultyLevel;
      if (this->applesEaten % 10 == 0)
      {
        if (this->difficultyLevel < 15)
        {
          this->difficultyLevel++;
        }
      }
    }
  }
}

void Engine::update()
{
  double tickDuration = 0.25 / difficultyLevel;
  if (GetTime() - lastTickTime > tickDuration)
  {
    tick();
    lastTickTime = GetTime();
  }
}

void Engine::handleKeypress()
{
  int lastKey = 0;
  int key = 0;
  while ((key = GetKeyPressed())) {
    lastKey = key;
  }

  switch (lastKey) {
  case KEY_DOWN:
    this->snakeDirection = point{0, 1};
    break;
  case KEY_UP:
    this->snakeDirection = point{0, -1};
    break;
  case KEY_LEFT:
    this->snakeDirection = point{-1, 0};
    break;
  case KEY_RIGHT:
    this->snakeDirection = point{1, 0};
    break;
  case KEY_SPACE:
      this->init();
    break;
  }
}

void Engine::render()
{
  switch (this->mode)
  {
  case GAME:
  {

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTextureQuad(mudTexture, Vector2{50, 30}, Vector2{0, 0}, Rectangle{0, 0, 800, 480}, WHITE);
    DrawText(TextFormat("Score: %08i", this->score), 10, 481, 14, WHITE);
    this->level->draw(this->wallTexture);
    if (isOnScreen(apple->getPosition()))
    {
      apple[0].draw(appleTexture);
    }
    snake->draw(this->snakeBodyTexture, this->snakeHeadTexture, this->snakeAngleTexture, this->snakeTailTexture);
    EndDrawing();
  }
  break;
  case GAMEOVER:
  {
    BeginDrawing();
    ClearBackground(RED);
    EndDrawing();
  }
  break;
  case LEADERBOARD:
  {
  }
  break;
  case EDITOR:
  {
  }
  break;
  case START:
  {
  }
  break;
  default:
  {
  }
  break;
  }
}