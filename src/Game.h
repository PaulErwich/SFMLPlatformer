
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameStates/GameStateBase.h"
#include "GameStates/GameMenu.h"
#include "GameStates/GameLevelSelect.h"
#include "GameStates/GamePlay.h"
#include "GameStates/GamePaused.h"
#include "GameStates/GameOver.h"
#include "GameStates/GameWin.h"
#include "GameStates/GameControls.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void input(sf::Event event);
  void update(float dt);
  void render();

 private:
  sf::RenderWindow& window;

  sf::Font font;

  sf::Sprite sprite;
  sf::Texture texture;

  GameMenu* game_menu;
  GameLevelSelect* game_level_select;
  GamePlay* game_play;
  GamePaused* game_paused;
  GameOver* game_over;
  GameWin* game_win;
  GameControls* game_controls;

  GameStateBase* current_state;
};

#endif // PLATFORMER_GAME_H
