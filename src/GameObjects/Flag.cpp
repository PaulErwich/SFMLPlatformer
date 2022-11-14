//
// Created by perwi on 14/04/2022.
//

#include "Flag.h"

Flag::Flag(sf::RenderWindow& game_window) :
  GameObject(game_window)
{

}

bool Flag::init(float x, float y)
{
  if (!texture->loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0111.png"))
  {
    return false;
  }

  if (!pole_texture.loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0131.png"))
  {
    return false;
  }

  sprite->setTexture(*texture);
  pole.setTexture(pole_texture);

  float scale = 60.0f/18.0f;

  sprite->setScale(scale, scale);
  pole.setScale(scale, scale);

  sprite->setPosition(x, y);
  pole.setPosition(x, y + 60);

  // Increased flag height because of the pole
  // This is for collision calculations
  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height * 2;

  setMin();
  calculateMax();

  return true;
}

void Flag::render()
{
  GameObject::render();
  window.draw(pole);
}