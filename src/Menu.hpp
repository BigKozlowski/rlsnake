#pragma once
#include "main.hpp"

enum menuItem
{
  LEVELSELECT,
  MAIN,
  LEADERBOARD,
  QUIT,
  EDITOR
};

class Menu
{
private:
  /* data */
public:
  Menu(/* args */);
  ~Menu();
  void drawButton(char *text, menuItem value);
};

Menu::Menu(/* args */)
{
}

Menu::~Menu()
{
}
