//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_HELPER_H
#define PLATFORMERSFML_HELPER_H

#include <SFML/Graphics.hpp>

class Helper
{
 public:
  static void SFMLText(sf::Text& text, const std::string& string, sf::Font& font,
                       int char_size, sf::Color color, float x, float y);
};

#endif // PLATFORMERSFML_HELPER_H
