//
// Created by MLG Erwich on 04/03/2022.
//

#include "GameLevelSelect.h"
GameLevelSelect::GameLevelSelect(
  STATE stateId, sf::RenderWindow& gameWindow, sf::Font& gameFont) :
  GameStateBase(stateId, gameWindow, gameFont)
{
  selected_level = 1;
  transition = false;

  for (int i = 0; i < MAX_LEVELS; i++)
  {
    levels[i] = new LevelIcon(window, i + 1, *font);
  }
}

GameLevelSelect::~GameLevelSelect()
{
  for (int i = 0; i < MAX_LEVELS; i++)
  {
    delete levels[i];
  }
}

bool GameLevelSelect::init()
{
  if (!block_texture.loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0009.png"))
  {
    std::cout << "block texture didn't load" << std::endl;
    return false;
  }

  Helper::SFMLText(title, "LEVEL SELECT", *font, 80, sf::Color::White,
                   window.getSize().x / 2, 100);

  int half_win = window.getSize().x / 2;
  int placement[MAX_LEVELS] = {half_win - 200, half_win, half_win + 200};

  for (int i = 0; i < MAX_LEVELS; i++)
  {
    levels[i]->init(block_texture, placement[i], window.getSize().y / 2);
  }
  return true;
}

void GameLevelSelect::reset()
{
  transition = false;
}

int GameLevelSelect::getSelectedLevel() const { return selected_level; }

void GameLevelSelect::input(sf::Event event)
{
  if (event.type == sf::Event::MouseButtonPressed)
  {
    sf::Vector2i click = sf::Mouse::getPosition(window);
    std::cout << click.x << ", " << click.y << std::endl;

    for (int i = 0; i < MAX_LEVELS; i++)
    {
      if (spriteClickChecker(click, levels[i]->getSprite()))
      {
        selected_level = levels[i]->getNumber();
        transition = true;
        break;
      }
    }
  }
}

STATE GameLevelSelect::update(float dt)
{
  if (transition)
  {
    return STATE::GAME_PLAY;
  }

  return game_state_id;
}

void GameLevelSelect::render()
{
  window.setView(window.getDefaultView());
  window.draw(title);

  for (int i = 0; i < MAX_LEVELS; i++)
  {
    levels[i]->render();
  }
}

