//
// Created by MLG Erwich on 04/03/2022.
//

#include "LevelIcon.h"
LevelIcon::LevelIcon(
  sf::RenderWindow& game_window, int level_number, sf::Font& icon_font) : window(game_window)
{
  font = &icon_font;
  texture = nullptr;
  number = level_number;
}

LevelIcon::~LevelIcon()
{
  delete font;
  delete texture;
}

bool LevelIcon::init(sf::Texture &icon_texture, float x, float y)
{
  texture = &icon_texture;
  sprite.setTexture(*texture);
  sprite.scale(5, 5);
  sprite.setPosition(x - sprite.getGlobalBounds().width / 2, y);

  Helper::SFMLText(text, std::to_string(number), *font, 40, sf::Color::White,
                   x, y + sprite.getGlobalBounds().height / 2);

  return true;
}

sf::Sprite& LevelIcon::getSprite() { return sprite; }

int LevelIcon::getNumber() { return number; }

void LevelIcon::update() {}

void LevelIcon::render()
{
  window.draw(sprite);
  window.draw(text);
}
