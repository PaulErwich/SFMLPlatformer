//
// Created by MLG Erwich on 28/04/2022.
//

#ifndef PLATFORMERSFML_LEVELTHREE_H
#define PLATFORMERSFML_LEVELTHREE_H

#include "Level.h"

class LevelThree : public Level
{
 public:
  LevelThree(sf::RenderWindow& game_window);
  ~LevelThree() = default;

  bool init(Player* _player, UI* _ui) override;

 private:
  void init_setup_blocks() override;
  void init_setup_platforms() override;
  void init_setup_enemies() override;
};

#endif // PLATFORMERSFML_LEVELTHREE_H
