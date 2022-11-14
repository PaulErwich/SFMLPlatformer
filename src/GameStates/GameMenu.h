//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_GAMEMENU_H
#define PLATFORMERSFML_GAMEMENU_H

#include "GameStateBase.h"

class GameMenu : public GameStateBase
{
 public:
  GameMenu(STATE stateId, sf::RenderWindow& gameWindow, sf::Font& gameFont);
  ~GameMenu() = default;

  bool init() override;
  void reset() override;
  void input(sf::Event event) override;
  STATE update(float dt) override;
  void render() override;

 private:
  sf::Text text_title;
  sf::Text text_play;
  sf::Text text_quit;

  sf::Text text_controls;

  STATE transition;

};

#endif // PLATFORMERSFML_GAMEMENU_H
