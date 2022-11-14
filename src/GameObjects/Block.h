//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_BLOCK_H
#define PLATFORMERSFML_BLOCK_H

#include "GameObject.h"

class Block : public GameObject
{
 public:
  Block(sf::RenderWindow& gameWindow);
  bool init(sf::Texture &block_texture, float x, float y);
};

#endif // PLATFORMERSFML_BLOCK_H
