//
// Created by MLG Erwich on 25/03/2022.
//

#include "Collectable.h"

Collectable::Collectable(sf::RenderWindow& game_window) :
  GameObject(game_window)
{

}

bool Collectable::init(sf::Texture& item_texture, float x, float y)
{
  texture = &item_texture;

  sprite->setTexture(*texture);
  sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);
  sprite->setScale(2, 2);

  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;

  sprite->setPosition(x + 30, y + 30);
  setMin();
  calculateMax();

  return true;
}

void Collectable::update(float dt)
{
  if (idle_clock.getElapsedTime().asSeconds() > 0.5)
  {
    
    idle_clock.restart();
  }
  sprite->move(0, movement.y);
}

void Collectable::setMin()
{
  min.x = sprite->getPosition().x - width / 2;
  min.y = sprite->getPosition().y - height / 2;
}

void Collectable::calculateMax()
{
  max.x = sprite->getPosition().x + width / 2;
  max.y = sprite->getPosition().y + height / 2;
}
