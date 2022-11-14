//
// Created by MLG Erwich on 27/04/2022.
//

#include "GameControls.h"

GameControls::GameControls(
  STATE stateId, sf::RenderWindow& game_window, sf::Font& game_font) :
  GameStateBase(stateId, game_window, game_font)
{
  transition = false;
}

bool GameControls::init()
{
  Helper::SFMLText(text_title, "CONTROLS", *font, 80, basic, window.getSize().x / 2, 50);

  //Helper::SFMLText()

  Helper::SFMLText(text_menu, "ENTER TO RETURN TO MENU", *font, 80, basic, window.getSize().x / 2, 1000);

  if (!texture.loadFromFile("Data/Images/Backgrounds/Controls.png"))
  {
    return false;
  }

  sprite.setTexture(texture);
  sprite.setScale(2, 2);

  return true;
}

void GameControls::reset()
{
  transition = false;
}

void GameControls::input(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      transition = true;
    }
  }
}

STATE GameControls::update(float dt)
{
  if (transition)
  {
    return STATE::GAME_MENU;
  }
  return game_state_id;
}

void GameControls::render()
{
  window.draw(sprite);
  window.draw(text_title);
  window.draw(text_control);
  window.draw(text_menu);
}
