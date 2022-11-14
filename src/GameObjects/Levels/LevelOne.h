//
// Created by MLG Erwich on 27/04/2022.
//

#ifndef PLATFORMERSFML_LEVELONE_H
#define PLATFORMERSFML_LEVELONE_H

#include "Level.h"

class LevelOne : public Level
{
 public:
  LevelOne(sf::RenderWindow& game_window);
  ~LevelOne() = default;

  bool init(Player* _player, UI* _ui) override;

 private:
  void init_setup_blocks() override;
  void init_setup_platforms() override;
  void init_setup_enemies() override;
};

#endif // PLATFORMERSFML_LEVELONE_H
