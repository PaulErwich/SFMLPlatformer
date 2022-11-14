//
// Created by MLG Erwich on 28/04/2022.
//

#ifndef PLATFORMERSFML_LEVELTWO_H
#define PLATFORMERSFML_LEVELTWO_H

#include "Level.h"

class LevelTwo : public Level
{
 public:
  LevelTwo(sf::RenderWindow& game_window);
  ~LevelTwo();

  bool init(Player* _player, UI* _ui) override;

 private:
  void init_setup_blocks() override;
  void init_setup_platforms() override;
  void init_setup_enemies() override;
};

#endif // PLATFORMERSFML_LEVELTWO_H
