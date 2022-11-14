//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_GAMEWIN_H
#define PLATFORMERSFML_GAMEWIN_H

#include "GameStateBase.h"
#include "../Extra/Helper.h"

class GameWin : public GameStateBase
{
 public:
  GameWin(STATE stateId, sf::RenderWindow& gameWindow, sf::Font& gameFont);
  ~GameWin() = default;
  bool init() override;
  void reset(int new_score);
  void input(sf::Event event) override;
  STATE update(float dt) override;
  void render() override;

 private:
  sf::Text text_win;
  sf::Text return_to_menu;
  sf::Text final_score;

  int score;

  bool transition;
};

#endif // PLATFORMERSFML_GAMEWIN_H
