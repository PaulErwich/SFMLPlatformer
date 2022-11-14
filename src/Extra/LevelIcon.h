//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_LEVELICON_H
#define PLATFORMERSFML_LEVELICON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Helper.h"

class LevelIcon
{
 public:
  LevelIcon(sf::RenderWindow& game_window, int level_number, sf::Font &icon_font);
  ~LevelIcon();
  bool init(sf::Texture &icon_texture, float x, float y);

  sf::Sprite& getSprite();
  int getNumber();

  void update();
  void render();

 private:
  sf::RenderWindow &window;
  sf::Font *font;

  sf::Texture *texture;
  sf::Sprite sprite;
  sf::Text text;

  int number;
};

#endif // PLATFORMERSFML_LEVELICON_H
