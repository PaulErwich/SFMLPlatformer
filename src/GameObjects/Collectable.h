//
// Created by MLG Erwich on 25/03/2022.
//

#ifndef PLATFORMERSFML_COLLECTABLE_H
#define PLATFORMERSFML_COLLECTABLE_H

#include "GameObject.h"

class Collectable : public GameObject
{
 public:
  Collectable(sf::RenderWindow& game_window);

  bool init(sf::Texture &item_texture, float x, float y);
  void update(float dt) override;
  void setMin() override;
  void calculateMax() override;

 private:
  sf::Clock idle_clock;
};

#endif // PLATFORMERSFML_COLLECTABLE_H
