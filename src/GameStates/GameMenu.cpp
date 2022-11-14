//
// Created by MLG Erwich on 04/03/2022.
//

#include "GameMenu.h"

GameMenu::GameMenu(
  STATE stateId, sf::RenderWindow& gameWindow, sf::Font& gameFont) :
  GameStateBase(stateId, gameWindow, gameFont)
{
  transition = STATE::GAME_MENU;
}

bool GameMenu::init()
{
  Helper::SFMLText(text_title, "PLATFORMER", *font, 80, basic,
                   window.getSize().x / 2, 100);
  Helper::SFMLText(text_play, "PLAY", *font, 40, basic,
                   window.getSize().x / 4, window.getSize().y / 2);
  Helper::SFMLText(text_quit, "QUIT", *font, 40, basic,
                   window.getSize().x / 4 + window.getSize().x / 2, window.getSize().y / 2);
  Helper::SFMLText(text_controls, "CONTROLS", *font, 40, basic,
                   window.getSize().x / 2, window.getSize().y / 2);

  return true;
}

void GameMenu::reset()
{
  transition = STATE::GAME_MENU;
}

void GameMenu::input(sf::Event event)
{
  if (event.type == sf::Event::MouseButtonPressed)
  {
    sf::Vector2i click = sf::Mouse::getPosition(window);

    if (clickChecker(click, text_play))
    {
      transition = STATE::GAME_LEVEL_SELECT;
    }

    if (clickChecker(click, text_quit))
    {
      transition = STATE::GAME_EXIT;
    }

    if (clickChecker(click, text_controls))
    {
      transition = STATE::GAME_CONTROLS;
    }
  }
}

STATE GameMenu::update(float dt)
{
  return transition;
}

void GameMenu::render()
{
  window.draw(text_title);
  window.draw(text_play);
  window.draw(text_controls);
  window.draw(text_quit);
}
