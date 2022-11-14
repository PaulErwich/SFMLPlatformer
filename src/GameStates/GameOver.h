//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_GAMEOVER_H
#define PLATFORMERSFML_GAMEOVER_H

#include "GameStateBase.h"
#include "../Extra/Helper.h"

class GameOver : public GameStateBase
{
 public:
  GameOver(STATE stateId, sf::RenderWindow& gameWindow, sf::Font& gameFont);
  ~GameOver() = default;
  bool init() override;

  void reset(int new_score);

  void input(sf::Event event) override;
  STATE update(float dt) override;
  void render() override;

 private:
  sf::Text text_lose;
  sf::Text return_to_menu;
  sf::Text final_score;

  int score;

  bool transition;
};

#endif // PLATFORMERSFML_GAMEOVER_H
