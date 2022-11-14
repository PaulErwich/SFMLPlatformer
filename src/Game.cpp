
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));

  font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf");

  game_menu = new GameMenu(STATE::GAME_MENU, window, font);
  game_level_select = new GameLevelSelect(STATE::GAME_LEVEL_SELECT, window, font);
  game_play = new GamePlay(STATE::GAME_PLAY, window, font);
  game_paused = new GamePaused(STATE::GAME_PAUSED, window, font);
  game_over = new GameOver(STATE::GAME_OVER, window, font);
  game_win = new GameWin(STATE::GAME_WIN, window, font);
  game_controls = new GameControls(STATE::GAME_CONTROLS, window, font);

  current_state = game_menu;
}

Game::~Game()
{
  delete game_menu;
  delete game_level_select;
  delete game_play;
  delete game_paused;
  delete game_over;
  delete game_win;
  delete game_controls;

  delete current_state;
}

bool Game::init()
{
  game_paused->setGamePlay(*game_play);

  if (!texture.loadFromFile("Data/Images/Backgrounds/backgroundtest.jpg"))
  {
    std::cout << "Menu texture didn't load." << std::endl;
    return false;
  }
  texture.setRepeated(true);

  sprite.setTexture(texture);
  sprite.setScale(3, 3);
  sprite.setTextureRect(sf::IntRect(0, 0, 2880, 1080));

  if (game_menu->init() && game_level_select->init() && game_play->init() &&
      game_paused->init() && game_over->init() && game_win->init() && game_controls->init())
  {
    return true;
  }

  return false;
}

void Game::input(sf::Event event)
{
  current_state->input(event);

  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Enter)
    {

    }
  }
}

void Game::update(float dt)
{
  STATE new_state = current_state->update(dt);

  if (new_state == current_state->getStateID())
  {

  }
  else
  {
    if (new_state != STATE::GAME_PLAY || new_state != STATE::GAME_PAUSED)
    {
      window.setView(window.getDefaultView());
    }

    switch(new_state)
    {
      case STATE::GAME_EXIT:
        window.close();
        break;
      case STATE::GAME_MENU:
        game_menu->reset();
        current_state = game_menu;
        break;
      case STATE::GAME_LEVEL_SELECT:
        game_level_select->reset();
        current_state = game_level_select;
        break;
      case STATE::GAME_PLAY:
        if (!game_paused->getPaused())
        {
          game_play->reset();
        }
        game_play->setLevel(game_level_select->getSelectedLevel());
        current_state = game_play;
        break;
      case STATE::GAME_PAUSED:
        game_paused->reset();
        current_state = game_paused;
        break;
      case STATE::GAME_OVER:
        game_over->reset(game_play->getScore());
        current_state = game_over;
        break;
      case STATE::GAME_WIN:
        game_win->reset(game_play->getScore());
        current_state = game_win;
        break;
      case STATE::GAME_CONTROLS:
        game_controls->reset();
        current_state = game_controls;
        break;
      case STATE::GAME_UNKNOWN:
        std::cout << "Unable to handle game state";
        break;
      default:
        std::cout << "unknown state";
        window.close();
        break;
    }
  }
}

void Game::render()
{
  window.draw(sprite);
  current_state->render();
}


