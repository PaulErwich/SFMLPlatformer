//
// Created by MLG Erwich on 04/03/2022.
//

#include "GamePaused.h"
GamePaused::GamePaused(
  STATE stateId, sf::RenderWindow& gameWindow, sf::Font& gameFont) :
  GameStateBase(stateId, gameWindow, gameFont)
{
  game_play = nullptr;
}

GamePaused::~GamePaused()
{
  delete game_play;
}

bool GamePaused::init()
{
  Helper::SFMLText(text_paused, "PAUSED", *font, 80, basic, window.getSize().x / 2, 50);

  Helper::SFMLText(text_unpause, "PRESS ESC TO UNPAUSE", *font, 80, basic, window.getSize().x / 2, 900);

  return true;
}

void GamePaused::reset()
{
  unpause = false;
}

void GamePaused::setGamePlay(GamePlay& game) { game_play = &game; }

bool GamePaused::getPaused() const { return unpause; }

void GamePaused::input(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Escape)
    {
      unpause = true;
    }
  }
}

STATE GamePaused::update(float dt)
{
  if (unpause)
  {
    game_play->setPause(false);
    return STATE::GAME_PLAY;
  }

  return game_state_id;
}

void GamePaused::render()
{
  game_play->render();
  window.draw(text_paused);
  window.draw(text_unpause);
}
