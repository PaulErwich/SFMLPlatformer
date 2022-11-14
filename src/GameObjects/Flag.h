//
// Created by perwi on 14/04/2022.
//

#ifndef PLATFORMERSFML_FLAG_H
#define PLATFORMERSFML_FLAG_H

#include "GameObject.h"

class Flag : public GameObject
{
 public:
  Flag(sf::RenderWindow &game_window);

  bool init(float x, float y);
  void render() override;

 private:
  sf::Sprite pole;
  sf::Texture pole_texture;
};

#endif // PLATFORMERSFML_FLAG_H
