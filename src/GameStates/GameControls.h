//
// Created by MLG Erwich on 27/04/2022.
//

#ifndef PLATFORMERSFML_GAMECONTROLS_H
#define PLATFORMERSFML_GAMECONTROLS_H

#include "GameStateBase.h"

class GameControls : public GameStateBase
{
 public:
  GameControls(STATE stateId, sf::RenderWindow& game_window, sf::Font& game_font);
  ~GameControls() = default;

  bool init() override;
  void reset() override;
  void input(sf::Event event) override;
  STATE update(float dt) override;
  void render() override;

 private:
  sf::Text text_title;

  sf::Texture texture;
  sf::Sprite sprite;

  sf::Text text_control;
  sf::Text text_menu;

  bool transition;
};

#endif // PLATFORMERSFML_GAMECONTROLS_H
