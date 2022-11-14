//
// Created by MLG Erwich on 04/03/2022.
//

#include "GameOver.h"
GameOver::GameOver(
  STATE stateId, sf::RenderWindow& gameWindow, sf::Font& gameFont) :
  GameStateBase(stateId, gameWindow, gameFont)
{
  score = 0;
}

bool GameOver::init()
{
  Helper::SFMLText(text_lose, "GAME OVER", *font, 80, basic, window.getSize().x / 2, 100);

  Helper::SFMLText(return_to_menu, "ENTER TO RETURN TO MENU", *font, 80, basic, window.getSize().x / 2, 900);
  return true;
}

void GameOver::reset(int new_score)
{
  score = new_score;
  Helper::SFMLText(final_score, "FINAL SCORE: " + std::to_string(score), *font, 80, basic, window.getSize().x / 2, 540);
  transition = false;
}

void GameOver::input(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      transition = true;
    }
  }
}

STATE GameOver::update(float dt)
{
  if (transition)
  {
    return STATE::GAME_MENU;
  }

  return game_state_id;
}

void GameOver::render()
{
  window.draw(text_lose);
  window.draw(return_to_menu);
  window.draw(final_score);
}
