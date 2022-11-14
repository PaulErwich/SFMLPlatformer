//
// Created by MLG Erwich on 04/03/2022.
//

#include "Block.h"
Block::Block(sf::RenderWindow& gameWindow) : GameObject(gameWindow)
{

}

bool Block::init(sf::Texture &block_texture, float x, float y)
{
  texture = &block_texture;

  sprite->setTexture(*texture);
  float scale = 60.0f / 18.0f;
  sprite->scale(scale, scale);

  sprite->setPosition(x, y);
  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;
  setMin();
  calculateMax();
  return true;
}
