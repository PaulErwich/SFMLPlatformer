//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_GAMESTATEBASE_H
#define PLATFORMERSFML_GAMESTATEBASE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Extra/Helper.h"

enum class STATE
{
  GAME_UNKNOWN = -1,
  GAME_EXIT = 0,
  GAME_MENU = 1,
  GAME_LEVEL_SELECT = 2,
  GAME_PLAY = 3,
  GAME_PAUSED = 4,
  GAME_OVER = 5,
  GAME_WIN = 6,
  GAME_CONTROLS = 7
};

class GameStateBase
{
 public:
  GameStateBase(STATE state_id, sf::RenderWindow& game_window, sf::Font &game_font);
  ~GameStateBase();
  virtual bool init();
  STATE getStateID();
  virtual void reset();
  virtual void input(sf::Event event);
  virtual STATE update(float dt);
  virtual void render();

 protected:
  static bool clickChecker(sf::Vector2i click, const sf::Text& area);
  static bool spriteClickChecker(sf::Vector2i click, const sf::Sprite& area);

  STATE game_state_id;
  sf::RenderWindow& window;
  sf::Font* font;

  const sf::Color basic = sf::Color::White;
};

#endif // PLATFORMERSFML_GAMESTATEBASE_H
