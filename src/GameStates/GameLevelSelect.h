//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_GAMELEVELSELECT_H
#define PLATFORMERSFML_GAMELEVELSELECT_H

#include "GameStateBase.h"
#include "../Extra/LevelIcon.h"

class GameLevelSelect : public GameStateBase
{
 public:
  GameLevelSelect(
    STATE stateId, sf::RenderWindow& gameWindow, sf::Font& gameFont);
  ~GameLevelSelect();
  bool init() override;
  void reset() override;
  int getSelectedLevel() const;
  void input(sf::Event event) override;
  STATE update(float dt) override;
  void render() override;

 private:
  static const int MAX_LEVELS = 3;
  sf::Text title;
  LevelIcon *levels[MAX_LEVELS];
  sf::Texture block_texture;

  int selected_level;

  bool transition;

};

#endif // PLATFORMERSFML_GAMELEVELSELECT_H
